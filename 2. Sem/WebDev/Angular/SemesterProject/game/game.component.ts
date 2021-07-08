import { stringify } from '@angular/compiler/src/util';
import { Component, OnInit } from '@angular/core';
import {
  HttpClient,
  HttpHeaders,
  JsonpClientBackend,
} from '@angular/common/http';

@Component({
  selector: 'app-game',
  templateUrl: './game.component.html',
  styleUrls: ['./game.component.css'],
})
export class GameComponent implements OnInit {
  httpOptions = {
    headers: new HttpHeaders({ 'Content-Type': 'application/json' }),
  };
  username: string = sessionStorage.getItem('username');
  highscore: string="";
  formValue: string = "";
  jsonFormValue = "";
  solved = function () {
    if (document.getElementById("solved")!=null&&sessionStorage.getItem("username")!=null) {
      this.highscore=sessionStorage.getItem("currentScore");
      return true;
    }
    else {
      return false;
    }
  }
  constructor(private http: HttpClient) {}

  onClick() {
    location.reload();
  }

  onSolved() {
    this.formValue ='{ "email":"' +this.username +'" , "highscore":"' +this.highscore +'" }';
    this.jsonFormValue = JSON.parse(this.formValue);
    this.http.post<{ message: string }>('http://localhost:3000/highscore',this.formValue,this.httpOptions).subscribe({
        next: (responseData) => {
          window.location.href = 'http://localhost:4200';
        },
        error: (err) => {},
      });
  }

  ngOnInit(): void {
    
    let secs = 0;
    function timer() {
      if (isSolved() != true) {
        secs++;
        document.getElementById('zeitlabel').innerHTML = secs.toString();
        setTimeout(function () {
          timer();
        }, 1000);
      }
    }

    //GAME START
    const riddle = document.createElement('div');
    riddle.id = 'riddle';
    document.body.appendChild(riddle);
    const puzzlePartsIdx = shufflePuzzleParts();

    for (let i = 0; i < puzzlePartsIdx.length; i++) {
      const img = document.createElement('img');
      const imgId = 'part' + puzzlePartsIdx[i];
      img.setAttribute('src', 'assets/images/img' + puzzlePartsIdx[i] + '.jpg');
      img.setAttribute('alt', imgId);
      img.setAttribute('id', imgId);
      img.addEventListener('click', () => {
        const currentImgId = img.getAttribute('id')!;
        const imgElement = document.getElementById(currentImgId)!;
        if (!isSolved()) {
          if (isSelectable()) {
            const firstSelectedPuzzlePartId = getAlreadySelectedPicId();
            imgElement.style.opacity = '1.0';
            if (imgElement.style.opacity != '0.6') {
              imgElement.style.opacity = '0.6';
            }
            if (countSelected() > 1) {
              if (areNeighbours(firstSelectedPuzzlePartId, currentImgId)) {
                swapParts();
              }
              resetOpacity();
            }
          }
        }
      });
      riddle.appendChild(img);
    }

    timer();

    function isSelectable() {
      return countSelected() <= 1;
    }

    function countSelected() {
      const pics = riddle.getElementsByTagName('img');
      let counter = 0;
      for (let i = 0; i < pics.length; i++) {
        if (pics[i].style.opacity == '0.6') {
          counter++;
        }
      }
      return counter;
    }

    function getAlreadySelectedPicId() {
      const pics = riddle.getElementsByTagName('img');
      let counter = 0;
      for (let i = 0; i < pics.length; i++) {
        if (pics[i].style.opacity == '0.6') {
          return pics[i].getAttribute('id')!;
        }
      }
      return '';
    }

    function isSolved() {
      const pics = riddle.getElementsByTagName('img');
      for (let i = 0; i < pics.length; i++) {
        const pic = 'part' + (i + 1).toString();
        const element = pics[i].getAttribute('id');
        if (pic != element) {
          return false;
        }
      }
      return true;
    }

    function shufflePuzzleParts() {
      const puzzleParts = [1, 2, 3, 4, 5, 6, 7, 8, 9];
      let counter = puzzleParts.length;
      while (counter > 0) {
        const index = Math.floor(Math.random() * counter);
        counter--;
        const temp = puzzleParts[counter];
        puzzleParts[counter] = puzzleParts[index];
        puzzleParts[index] = temp;
      }
      return puzzleParts;
    }

    function areNeighbours(firstPicId: string, secondPicId: string) {
      const pics = riddle.getElementsByTagName('img');

      for (let i = 0; i < pics.length; i++) {
        if (pics[i].getAttribute('id') == firstPicId) {
          const neighbourIdxs = getNeighbourIdxs(i);
          for (let j = 0; j < neighbourIdxs.length; j++) {
            if (pics[neighbourIdxs[j]].getAttribute('id') == secondPicId) {
              return true;
            }
          }
        }
      }
      return false;
    }

    function swapParts() {
      const pics = riddle.getElementsByTagName('img');
      let pic1 = null;

      for (let i = 0; i < pics.length; i++) {
        if (pics[i].style.opacity == '0.6') {
          if (pic1 == null) {
            pic1 = document.getElementById(pics[i].getAttribute('id')!);
            continue;
          }
          let pic2 = document.getElementById(pics[i].getAttribute('id')!)!;
          const pic1Source = pic1.getAttribute('src')!;
          const pic1Alt = pic1.getAttribute('alt')!;
          const pic1Id = pic1.getAttribute('id')!;
          const pic2Source = pic2.getAttribute('src')!;
          const pic2Alt = pic2.getAttribute('alt')!;
          const pic2Id = pic2.getAttribute('id')!;
          pic1.setAttribute('src', pic2Source);
          pic1.setAttribute('alt', pic2Alt);
          pic1.setAttribute('id', pic2Id);
          pic2.setAttribute('src', pic1Source);
          pic2.setAttribute('alt', pic1Alt);
          pic2.setAttribute('id', pic1Id);
          if (isSolved()) {
            let highscore = 100 - secs;
            let str: string = ' ' + 'Points: ' + highscore + '';
            let solved = document.createElement('div');
            solved.id = 'solved';
            const linkText = document.createTextNode('SOLVED!');
            const scoreText = document.createTextNode(str);
            solved.appendChild(linkText);
            solved.appendChild(scoreText);
            riddle.appendChild(solved);
            sessionStorage.setItem("currentScore",highscore.toString());
          }
          break;
        }
      }
    }

    function resetOpacity() {
      const pics = riddle.getElementsByTagName('img');
      for (let i = 0; i < pics.length; i++) {
        if (pics[i].style.opacity == '0.6') {
          pics[i].style.opacity = '1.0';
        }
      }
    }

    function getNeighbourIdxs(currentIdx: number) {
      const returnIdxs: number[] = [];
      if (isNeighbourIndexCol(currentIdx - 3)) {
        returnIdxs.push(currentIdx - 3);
      }
      if (isNeighbourIndexRow(currentIdx, currentIdx + 1)) {
        returnIdxs.push(currentIdx + 1);
      }
      if (isNeighbourIndexCol(currentIdx + 3)) {
        returnIdxs.push(currentIdx + 3);
      }
      if (isNeighbourIndexRow(currentIdx, currentIdx - 1)) {
        returnIdxs.push(currentIdx - 1);
      }
      return returnIdxs;
    }

    function isNeighbourIndexRow(currentIdx: number, checkIdx: number) {
      return (
        Math.max(-1, checkIdx) > -1 &&
        Math.min(9, checkIdx) < 9 &&
        Math.floor(currentIdx / 3) == Math.floor(checkIdx / 3)
      );
    }

    function isNeighbourIndexCol(checkIdx: number) {
      return Math.max(-1, checkIdx) > -1 && Math.min(9, checkIdx) < 9;
    }
    //GAME END
  }
}
