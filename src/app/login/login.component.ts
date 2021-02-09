import { Component, OnInit } from '@angular/core';
import {Router} from '@angular/router';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {

  username: string;
  password: string;
  connectionError: string;
  constructor(private router: Router) {
    this.username = '';
    this.password = '';
    this.connectionError = '';
  }

  ngOnInit(): void {
  }

  onClickValiderButton($event): void {
    if (this.username === 'mouen0807' && this.password === 'azer0807') {
      this.router.navigateByUrl('/home');
    }
    else{
      this.connectionError = 'Erreur de connexion';
    }
  }
}

