import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormControl, FormGroup, Validators, ReactiveFormsModule, FormsModule } from '@angular/forms';

@Component({
  selector: 'app-signup',
  templateUrl: './signup.component.html',
  styleUrls: ['./signup.component.css']
})

export class SignupComponent implements OnInit {

  registerForm = new FormGroup({
    email: new FormControl('', [Validators.required, Validators.email]),
    passwordOne: new FormControl('', [Validators.required, Validators.minLength(8)]),
    passwordTwo: new FormControl('', [Validators.required, Validators.minLength(8)]),
    firma: new FormControl({ value: "FH Technikum Wien", disabled: true }),
    adresse: new FormControl(''),
    plz: new FormControl('', [Validators.pattern("^[0-9]{4}$")])
  });


  getErrorMessage(parameter) {
    switch (parameter) {
      case "email":
        if (this.registerForm.get('email').hasError('requried')) {
          return 'Eingabe fehlt';
        }
        if (this.registerForm.get('email').hasError('email')) {
          return 'Ungültige Email';
        }
        break;
      case "password1":
        if (this.registerForm.get('passwordOne').hasError('required')) {
          return 'Passwort fehlt';
        }
        if (this.registerForm.get('passwordOne').hasError('minlength')) {
          return 'Passwort muss mindestens 8 Stellen haben';
        }
        break;
      case "password2":
        if (this.registerForm.get('passwordTwo').hasError('required')) {
          return 'Passwort fehlt';
        }
        if (this.registerForm.get('passwordTwo').hasError('required')) {
          return 'Passwort muss mindestens 8 Stellen haben';
        }
        break;
      case "plz":
        if (this.registerForm.get('plz').hasError('pattern')) {
          return 'Das ist keine PLZ';
        }
        break;
      default:
        break;
    }
  }

  hide = true;
  constructor() { }

  ngOnInit(): void {
  }

  onSubmit() {

    var obj = this.registerForm.value;

    if (obj['passwordOne'] != obj['passwordTwo']) {

      alert("Passwörter stimmen nicht überein")
    }
    else {
      
      this.registerForm.reset();
    }
  }
}
