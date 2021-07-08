import { Component, OnInit } from '@angular/core';
import {
  HttpClient,
  HttpHeaders,
  HttpParams,
  JsonpClientBackend,
} from '@angular/common/http';

@Component({
  selector: 'app-profile',
  templateUrl: './profile.component.html',
  styleUrls: ['./profile.component.css']
})
export class ProfileComponent implements OnInit {
  email:string=sessionStorage.getItem("username");
  highscore:string="";
  constructor(private http: HttpClient) {}
  formValue: string = "";
  jsonFormValue = "";
  ngOnInit(): void {
    if (document.contains(document.getElementById("riddle"))) 
    {
      document.getElementById("riddle").remove();
    }   
    this.onGetHighscore();
  }
  onGetHighscore() {
    let headers = new HttpHeaders().append('Content-Type', 'application/json');
    let params = new HttpParams().append('email',this.email);
    this.http.get<{}>('http://localhost:3000/profile', { headers: headers, params: params }).subscribe({//napravi da vadi samo za usera
      next: (responseData) => {
        let str=JSON.stringify(responseData);
        str=str.substring(0,str.length-27);
        str=str.substring(str.length-2,str.length);
        this.highscore=str;
      },
      error: (err) => {

      },
    });
  }

}
