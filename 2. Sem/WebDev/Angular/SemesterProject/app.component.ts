import { HttpClient, HttpHeaders, JsonpClientBackend } from '@angular/common/http';
import { Component } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css'],
})
export class AppComponent {

  httpOptions = {
    headers: new HttpHeaders({ 'Content-Type': 'application/json' })
  };
  constructor(private http: HttpClient) { }

  ngOnInit(): void {
  }

  title = 'SemesterProject';
  func = function () {
    if (sessionStorage.getItem("token") != null) {
      return true;
    }
    else {
      return false;
    }
  }

  onLogout() {
    this.http.post<{ message: string }>('http://localhost:3000/logout', this.httpOptions).subscribe({
      next: (responseData) => {
        sessionStorage.removeItem("token");
        sessionStorage.removeItem("username");
        console.log(responseData.message);
        window.location.href = 'http://localhost:4200/login';
      },
      error: (err) => {

      },
    });

  }
}