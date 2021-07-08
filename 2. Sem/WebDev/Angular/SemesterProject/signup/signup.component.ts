import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Component, OnInit } from '@angular/core';
import { FormControl, NgForm } from '@angular/forms';
import { Validators } from '@angular/forms';

@Component({
  selector: 'app-signup',
  templateUrl: './signup.component.html',
  styleUrls: ['./signup.component.css']
})
export class SignupComponent implements OnInit {
  email = new FormControl('', [
    Validators.required,
    Validators.email
  ]);
  emailString: string = "";
  firstPassword: string = "";
  secondPassword: string = "";
  hide = true;
  hideSecond = true;
  isLoading = false;
  formValue: string = "";
  jsonFormValue = "";
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
  onSubmit() {
    this.emailString = (<HTMLInputElement>document.getElementById("email")).value;
    this.firstPassword = (<HTMLInputElement>document.getElementById("password")).value;
    this.secondPassword = (<HTMLInputElement>document.getElementById("secondPassword")).value;
    if (this.firstPassword == this.secondPassword && this.firstPassword.length >= 8 && this.emailString != "") {
      this.formValue = '{ "email":"' + this.emailString + '" , "password":"' + this.firstPassword + '" }';
      this.jsonFormValue = JSON.parse(this.formValue);
      this.http.post<{ message: string }>('http://localhost:3000/signup', this.jsonFormValue, this.httpOptions).subscribe({
        next: (responseData) => {
          sessionStorage.setItem("username",this.emailString);
          sessionStorage.setItem("token",responseData.message.substr(responseData.message.length-10,responseData.message.length));
          console.log(responseData.message);
          window.location.href='http://localhost:4200/home';
        },
        error: (err) => {
        },
      });
    }
    else {
      if (this.emailString == "") {
        console.log("Email is required.");
      }
      if (this.firstPassword == "" || this.secondPassword == "") {
        if (this.firstPassword == "") console.log("First Password is required.");
        if (this.secondPassword == "") console.log("Second Password is required.");
      }
      else {
        if (this.firstPassword.length < 8) {
          console.log("Password needs to have 8 or more letters.");
        }
        if (this.firstPassword != this.secondPassword) {
          console.log("Passwords do not match.");
        }
      }
    }

  }
}
