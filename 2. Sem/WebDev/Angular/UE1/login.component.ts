import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormControl, FormGroup, Validators, ReactiveFormsModule } from '@angular/forms';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {
  email_proto = "test@test.at";
  password_proto = "12345678";
  submitted = false;
  loginForm = new FormGroup({
      email: new FormControl('',[Validators.required, Validators.email]),
    password: new FormControl('', [Validators.required])
  });

  hide = true;
  constructor() { }

  ngOnInit(){
  }

  onSubmit(){
    var obj = this.loginForm.value;

    if(obj['email'] == this.email_proto && obj['password'] == this.password_proto)
    {
      console.log("Login sucessful");
    }
    else
    {
      console.log("Login Failed");
    }

    this.loginForm.reset();
    
  }
}
