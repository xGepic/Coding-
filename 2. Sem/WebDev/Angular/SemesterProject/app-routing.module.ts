import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { CommonModule } from '@angular/common';
import { LoginComponent } from './login/login.component';
import { SignupComponent } from './signup/signup.component';
import { FaqComponent } from './faq/faq.component';
import { HighscoreComponent } from './highscore/highscore.component';
import { ProfileComponent } from './profile/profile.component';
import { GameComponent } from './game/game.component';

const routes: Routes = [
  {path: 'login', component: LoginComponent},
  {path: 'signup', component: SignupComponent},
  {path: 'faq', component: FaqComponent},
  {path: 'highscore', component: HighscoreComponent},
  {path: 'profile', component: ProfileComponent},
  {path: 'game', component: GameComponent}
];

@NgModule({
  declarations: [],
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
