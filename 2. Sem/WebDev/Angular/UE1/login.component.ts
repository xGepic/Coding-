import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {

  hide = true;
  isLoading = false;

  constructor() { }

  ngOnInit(): void {

  }
  
  username: string = '';
  password: string = '';
  
  loginFunc() {

    let emailBool:boolean;

    if(this.username == "" && this.password == ""){
      console.log("Error! - Enter a Password")
      return
    }

    emailBool =(/^[a-zA-Z0-9.-_]{1,}@[a-zA-Z.-]{2,}[.]{1}[a-zA-Z]{2,}$/.test(this.username));

    if(emailBool == false){
      console.log("Login failed!")
    }
    if(emailBool == true) {
      console.log("Login successful!")
    }
  }
}
