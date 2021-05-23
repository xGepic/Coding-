import { HttpClient, HttpHeaders } from '@angular/common/http'
import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormControl, FormGroup, Validators, ReactiveFormsModule, NgForm } from '@angular/forms';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {

  email_proto = "test@test.at";
  password_proto = "12345678";
  submitted = false;
  hide = true;
  constructor(private http: HttpClient) { }
  httpOptions = {
    headers: new HttpHeaders({ 'Content-Type': 'application/json' })
  }

  loginForm = new FormGroup({

    email: new FormControl('', [Validators.required, Validators.email]),
    password: new FormControl('', [Validators.required])
  });

  ngOnInit() {
  }

  onSubmit(form: NgForm) {
    console.log(form.value);
    var obj = this.loginForm.value;
    this.http.post<{ message: string }>('http://localhost:3000/login', form.value, this.httpOptions).subscribe((responseData) => {
      console.log(responseData.message);
    })

    if (obj['email'] == this.email_proto && obj['password'] == this.password_proto) {
      console.log("Login sucessful");
    }
    else {
      console.log("Login Failed");
    }
    this.loginForm.reset();
  }
}
