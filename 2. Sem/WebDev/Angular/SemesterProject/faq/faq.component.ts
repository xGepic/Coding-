import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-faq',
  templateUrl: './faq.component.html',
  styleUrls: ['./faq.component.css']
})
export class FaqComponent implements OnInit {

  constructor() { }

  ngOnInit(): void {
    if (document.contains(document.getElementById("riddle"))) 
    {
      document.getElementById("riddle").remove();
    }   
  }

}
