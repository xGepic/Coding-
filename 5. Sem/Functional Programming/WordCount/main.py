import sys
import time
import pandas as pd
import numpy as np
import re
from pathlib import Path


class WordCount:
    def __init__(self, path, fileExtension):
        self.path = path
        self.fileExtension = fileExtension

    def WriteValuesToFile(self, values):
        f = open("outputs/"+self.path+".txt", "w")
        f.write(values.to_string())
        f.close()

    def GetWordsFromFiles(self):
        temp = []
        for p in Path(self.path).rglob('**/*'+self.fileExtension):
            temp.append(p.read_text().split())
        return temp

    def FlatMyList(self, tempList):
        temp = tempList
        temp = list(np.concatenate(temp).flat)
        return temp

    def MakeAlphaNum(self, tempList):
        temp = [re.split(r"[^A-Za-z0-9]+", x) for x in tempList]
        return temp

    def FixEmptyStrings(self, tempList):
        temp = [x for x in tempList if len(x) >= 1]
        return temp

    def MakeValues(self, tempList):
        values = tempList
        values = pd.value_counts(np.array(values))
        return values

    def MyWordCount(self):
        self.WriteValuesToFile(self.MakeValues(self.FixEmptyStrings(self.FlatMyList(
            self.MakeAlphaNum(self.FlatMyList(self.GetWordsFromFiles()))))))


start = time.time()
Test = WordCount(sys.argv[1], sys.argv[2])
Test.MyWordCount()
end = time.time()
print(f'Time: {((end-start)*1000):4.2f}ms')
