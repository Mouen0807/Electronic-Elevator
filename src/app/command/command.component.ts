import {Component, OnChanges, OnDestroy, OnInit, SimpleChanges} from '@angular/core';
import {CommandService} from '../services/command.service';
import {interval, Subscription} from 'rxjs';



@Component({
  selector: 'app-command',
  templateUrl: './command.component.html',
  styleUrls: ['./command.component.css']
})
export class CommandComponent implements OnInit{
  response: string;
  actualLevel: string;
  mySub: Subscription;
  test = true;

  constructor(public commandService: CommandService) {
    this.mySub = interval(2000).subscribe((func => {
      this.actualLevel = this.commandService.getActualLevel();
    }));
  }
  ngOnInit(): void {
   this.actualLevel = '0';
  }
  onClickArreter($event): void {
     this.commandService.stopElevator();
  }
  onClickLancer($event): void{
     this.commandService.startElevator();
  }
  onClickAppelButtonOrControlButton(value: number, $event): void{
    this.commandService.goToElevator(value);
  }


}


