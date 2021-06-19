import { Injectable } from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {Observable} from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class CommandService {

  /*public responseList: Category[];*/
  public url = 'http://192.168.1.100:9090/api/';
  public response: string;
  constructor(private http: HttpClient)  {
  }

  stopElevator(): string {
    this.http.get(this.url + 'stopElevator?stop=true', {responseType: 'text' })
      .subscribe(result => { this.response = result; });
    return this.response;
  }
  startElevator(): string{
    this.http.get(this.url + 'startElevator?start=true', {responseType: 'text' })
      .subscribe(result => { this.response = result; });
    return this.response;
  }
  goToElevator(level: number): string{
    this.http.get(this.url + 'goToLevel?number=' + level , {responseType: 'text' })
      .subscribe(result => { this.response = result; });
    return this.response;
  }
  goToElevatorInterior(level: number): string{
    this.http.get(this.url + 'goToLevelInterior?number=' + level , {responseType: 'text' })
      .subscribe(result => { this.response = result; });
    return this.response;
  }

  getActualLevel(): string{
    this.http.get(this.url + 'actualLevel', {responseType: 'text' })
      .subscribe(result => { this.response = result; });
    return this.response;
  }
}
