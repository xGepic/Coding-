import { HttpClient, HttpHeaders, JsonpClientBackend } from '@angular/common/http';
import { Component, OnInit } from '@angular/core';
import { FormControl, NgForm } from '@angular/forms';
import { Validators } from '@angular/forms';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {
  httpOptions = {
    headers: new HttpHeaders({ 'Content-Type': 'application/json' })
  };
  constructor(private http: HttpClient) { }
  ngOnInit(): void {
    if (document.contains(document.getElementById("riddle"))) 
    {
      document.getElementById("riddle").remove();
    }   
  }
  email = new FormControl('', [
    Validators.required,
    Validators.email
  ]);
  emailString: string = "";
  password: string = "";
  hide = true;
  isLoading = false;
  button = document.getElementById("login");
  formValue: string = "";
  jsonFormValue = "";
  onSubmit() {
    console.log(this.formValue);
    console.log(this.jsonFormValue);
    this.emailString = (<HTMLInputElement>document.getElementById("email")).value;
    this.password = (<HTMLInputElement>document.getElementById("password")).value;
    if (this.emailString != "" && this.password != "") {
      this.formValue = '{ "email":"' + this.emailString + '" , "password":"' + this.password + '" }';
      this.jsonFormValue = JSON.parse(this.formValue);
      this.http.post<{ message: string }>('http://localhost:3000/login', this.jsonFormValue, this.httpOptions).subscribe({
        next: (responseData) => {
          sessionStorage.setItem("username", this.emailString);
          sessionStorage.setItem("token", responseData.message.substr(responseData.message.length - 10, responseData.message.length));
          console.log(responseData.message);
          console.log(sessionStorage.getItem("token"));
          window.location.href = 'http://localhost:4200';
        },
        error: (err) => {

        },
      });
    }
    else {
      if (this.emailString == "") {
        console.log("Email needed.");
      }
      if (this.password == "") {
        console.log("Password needed.");
      }
    }

  }
}
