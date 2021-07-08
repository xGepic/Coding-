import { Component, OnInit, ViewChild } from '@angular/core';
import {
  HttpClient,
  HttpHeaders,
  JsonpClientBackend,
} from '@angular/common/http';
import { MatTable } from '@angular/material/table';

export interface TableRow {
  name: string;
  highscore: number;
}

@Component({
  selector: 'app-highscore',
  templateUrl: './highscore.component.html',
  styleUrls: ['./highscore.component.css']
})

export class HighscoreComponent implements OnInit {
  httpOptions = {
    headers: new HttpHeaders({ 'Content-Type': 'application/json' }),
  };
  
  constructor(private http: HttpClient) {}

  displayedColumns: string[] = ['name', 'highscore'];
  dataSource: TableRow[]=[];
  @ViewChild(MatTable,{static:true}) table: MatTable<any>;

  ngOnInit(): void {
    if (document.contains(document.getElementById("riddle"))) 
    {
      document.getElementById("riddle").remove();
    }   
    this.onGetHighscore();
  }

  onGetHighscore() {
    this.http.get<{}>('http://localhost:3000/highscore',this.httpOptions).subscribe({
      next: (responseData) => {
        let str=JSON.stringify(responseData);
        let myArr=str.split("},{");
        for(let i=0;i<myArr.length;i++)
        {
          let currentRow:TableRow={name:"",highscore:0};
          let number="";
          let name="";
          if(i==0)
          {
            number = myArr[i].substring(myArr[i].length-26,myArr[i].length-28);
            name = myArr[i].substring(11,myArr[i].length-43);
          }
          else if(i==myArr.length-1)
          {
            number = myArr[i].substring(myArr[i].length-28,myArr[i].length-30);
            name = myArr[i].substring(9,myArr[i].length-45);
          }
          else
          {
            number = myArr[i].substring(myArr[i].length-26,myArr[i].length-28);
            name = myArr[i].substring(9,myArr[i].length-43);
          }
          let numberInt: number=parseInt(number);
          let tempI=i+1;
          currentRow={name:name, highscore:numberInt};
          this.dataSource.push(currentRow);
        }
        this.dataSource.sort(function compareFn(firstEl, secondEl) { if(firstEl.highscore>secondEl.highscore) return -1; else if(firstEl.highscore<secondEl.highscore) return 1; else return 0; });
        this.table.renderRows()
      },
      error: (err) => {

      },
    });
  }

}
