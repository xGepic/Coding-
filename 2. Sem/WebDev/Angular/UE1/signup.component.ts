import { jsDocComment } from '@angular/compiler';
import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-signup',
  templateUrl: './signup.component.html',
  styleUrls: ['./signup.component.css']
})


export class SignupComponent implements OnInit {

  hide = true;
  isLoading = false;


  constructor() { }

  ngOnInit(): void {

  }

  userData = {

    firma: "FH Technikum Wien"
  }

  username: string = '';
  email: string = '';
  password1: string = '';
  password2: string = '';
  strasse: string = '';
  stadt: string = '';
  zip: string = '';

  signupFunc() {

    if(this.username == "" || this.email == "" || this.password1 == "" || this.password2 == ""){
      console.log("Error! - Fill out all mandatory fields!")
      return
    }

    if (this.password1 !== this.password2) {
      console.log("Error! - Password1 and Password2 are not identical!")
    }
    
    if (this.password1 == this.password2) {
      if (this.password1.length < 8 || this.password2.length < 8) {
        console.log("Error! - Password too short!")
        return
      }
      console.log("Success!")
    }
  }
}