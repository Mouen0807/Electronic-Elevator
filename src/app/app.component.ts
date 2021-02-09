import {Component, OnDestroy, OnInit} from '@angular/core';
import {Router, NavigationStart} from '@angular/router';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit{
  title = 'Elevator-Project';
  constructor(private router: Router) {
  }
  ngOnInit(): void{
  }
}
