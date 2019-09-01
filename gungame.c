/*
	A SHOOTING GAME
	Dependencies: DOS Graphics + TurboC comipler 
	Author: Senthilnathan, A
*/
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#include<alloc.h>
#include<dos.h>


void base();
void info();
void details();
void create_image();
void gundraw();
void gunbomb();
void enmyrt();
void enmylt();
void enmybomb();
void blastdraw();
void clearscreen();
void operations();
void startgame();
void explode(int,int);
void  showmouseptr();
void  hidemouseptr();
void  restrictmouseptr(int x1,int y1,int x2,int y2);
void  getmousepos(int *button,int *x,int *y);
void  hidemouseptr();
void reset();

 union REGS ii,oo;


/* check variables */
int health=50,enmy_health=14,rt_flight_no=7,lt_flight_no=7;
int lt_dir=0,rt_dir=0,ebn=0,gbn=0;
int lt_pos1[5]={600,500,450,330,120};
int lt_pos2[5]={580,460,410,280,70};
int rt_pos1[5]={30,150,320,510,610};
int rt_pos2[5]={60,130,270,468,550};

/* position parameters */
int rfx1,rfx2,rfy=25,lfx1,lfx2,lfy=50;
int gx1,gx2,gy=400;
int blx,bly;
int gb[30][4];
int eb[15][4];

/* images */
void *gun,*gun_bomb,*enmy_rt,*enmy_lt,*enmy_bomb,*blast;


void startgame()
     {
	    base();
	    settextstyle(5,0,1);
	    outtextxy(250,230,"Press any key !!!");
	    outtextxy(250,260,"To restart Press Esc");
	    setfillstyle(1,2);
	    bar(1,468,638,478);
	    setfillstyle(1,4);
	    bar(120,470,220,476);
	    settextstyle(0,0,0);
	    setcolor(14);
	    outtextxy(20,470,"YOUR HEALTH");
	    setfillstyle(1,4);
	    bar(500,470,598,476);
	    outtextxy(370,470,"ENEMIES HEALTH");
	    getch();
	    setfillstyle(1,1);
	    bar(250,230,420,300);
	    gx1=280;
	    putimage(gx1,gy,gun,COPY_PUT);
	    delay(1000);
	    operations();
	    reset();
	    main();
	   }


/* CONSTRUCTING THE BASE */
void base()
     {
	    char patterns[]= {0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x00};
	    setbkcolor(1);
	    setcolor(15);
	    rectangle(0,0,639,479);
	    /* BASE */
	    setfillpattern(&patterns[0],BROWN);
	    bar(1,456,638,478);
	    setfillstyle(1,BROWN);
	    bar(1,450,638,454);
	    /* TO CREATE OTHER MOVING OBJECTS */
	    create_image();
     }

/* CREATING OTHER MOVING IMAGES */
void create_image()
    {

      int area;

       gundraw();
	 area=imagesize(9,400,51,449);
	 gun=malloc(area);

       gunbomb();
	 area=imagesize(20,350,40,392);
	 gun_bomb=malloc(area);

       enmyrt();
	 area=imagesize(18,20,65,40);
	 enmy_rt=malloc(area);

       enmylt();
	 area=imagesize(120,20,167,40);
	 enmy_lt=malloc(area);

       enmybomb();
	 area=imagesize(42,41,58,58);
	 enmy_bomb=malloc(area);

       blastdraw();
	 area=imagesize(200,200,250,250);
	 blast=malloc(area);

       if(gun==NULL||gun_bomb==NULL||enmy_rt==NULL||enmy_lt==NULL||enmy_bomb==NULL||blast==NULL)
	    {
	      printf("\n\nInsufficient memory .... Press any key .... ");
	      getch();
	    }

	 getimage(9,400,51,449,gun);
	 getimage(20,350,40,392,gun_bomb);
	 getimage(18,20,65,40,enmy_rt);
	 getimage(120,20,167,40,enmy_lt);
	 getimage(42,41,58,58,enmy_bomb);
	 getimage(200,200,250,250,blast);

	clearscreen();

    }

/* DRAW GUN */
void gundraw()
    {
	setfillstyle(9,YELLOW);
	bar(10,420,50,449);
	setfillstyle(1,RED);
	bar(20,400,40,419);
	setcolor(RED);
	rectangle(10,420,50,449);

    }

/* DRAW GUN BOMB */
void gunbomb()
    {
	 int point[]={20,380,40,380,40,360,30,350,20,360,20,380};
	 setcolor(7);
	 setfillstyle(1,8);
	 drawpoly(6,point);
	 floodfill(30,360,7);
	 line(20,360,40,360);
	 setcolor(12);
	 setfillstyle(11,12);
	 bar(20,381,40,390);
    }

/* DRAW ENEMY FLIGHT IN RIGHT DIRECTION */
void enmyrt()
    {
       int point[]={20,20,30,35,55,25,65,35,60,40,20,40,20,20};
	 int point1[]={50,30,55,30,60,35,50,35,50,30};
	 setcolor(11);
	 setfillstyle(1,11);
	 drawpoly(7,point);
	 floodfill(45,35,11);
	 setcolor(8);
	 setfillstyle(1,8);
	 drawpoly(7,point1);
	 floodfill(55,33,8);


    }

/* DRAW ENEMY FLIGHT IN LEFT DIRECTION */
void enmylt()
    {
	 int point[]={165,20,155,35,130,25,120,35,125,40,165,40,165,20};
	 int point1[]={135,30,130,30,125,35,135,35,135,30};
	 setcolor(11);
	 setfillstyle(1,11);
	 drawpoly(7,point);
	 floodfill(145,35,11);
	 setcolor(8);
	 setfillstyle(1,8);
	 drawpoly(7,point1);
	 floodfill(130,33,8);
    }

/* DRAW ENEMY BOMB */
void enmybomb()
    {
	setcolor(7);
	setfillstyle(1,8);
	circle(50,50,8);
	floodfill(50,50,7);
    }

/* DRAW THE EXPLOSION */
void blastdraw()
    {
	 int point[]={205,205,212,212,220,200,223,212,233,206,228,217,241,218,234,224,250,225,235,230,230,240,225,233,218,250,213,237,206,240,209,233,200,230,212,221,205,205};
	 setcolor(14);
	 setfillstyle(1,LIGHTRED);
	 drawpoly(19,point);
	 floodfill(225,225,14);
    }

/* CLEAR THE SCREEN */
void clearscreen()
   {
     setfillstyle(1,1);
     bar(1,1,638,449);
   }


/* OPERATIONS */
void operations()
   {
	int ch,j,i,reset1=0,reset2=0;
	rfx1=1;
	lfx1=592;
       while((health>0)&&(enmy_health>0))
	   {
	       rfx1=rfx1+1;
	       lfx1=lfx1-1;
	       delay(10);
		if((rfx1+50<639)&&(rt_flight_no>0))
		 {
		   if(reset1==1)
		     {
		       rfx1=1;
		       reset1=0;
		     }
		   putimage(rfx1,rfy,enmy_rt,COPY_PUT);
		     if(rt_dir==1)
			 {
			    for(i=0;i<5;i++)
			      {
				if(rfx1==rt_pos1[i])
				  {
				     eb[ebn][0]=rfx1;
				     eb[ebn][1]=rfx1+50;
				     eb[ebn][2]=rfy+10;
				     eb[ebn][3]=1;
				     ebn++;
				     if(ebn==15)
				      ebn=0;

				     break;

				   }
			      }
			 }
		    else  if(rt_dir==0)
			 {
			    for(i=0;i<5;i++)
			      {
				if(rfx1==rt_pos2[i])
				  {
				     eb[ebn][0]=rfx1;
				     eb[ebn][1]=rfx1+50;
				     eb[ebn][2]=rfy+10;
				     eb[ebn][3]=1;
				     ebn++;
				     if(ebn==15)
				      ebn=0;
				     break;

				   }
			      }
			 }

		 }
		else
		  {
		    setfillstyle(1,1);
		    bar(rfx1,rfy,rfx1+46,rfy+20);
		    rfx1=1;
		  if(rt_dir==0)
		  rt_dir=1;
		  else
		  rt_dir=0;

		  }
	       if((lfx1>1)&&(lt_flight_no>0))
	       {
		 if(reset2==1)
		     {
		       lfx1=591;
		       reset2=0;
		     }

	       putimage(lfx1,lfy,enmy_lt,COPY_PUT);
		   if(lt_dir==0)
			 {
			    for(i=0;i<5;i++)
			      {
				if(lfx1==lt_pos1[i])
				  {
				     eb[ebn][0]=lfx1;
				     eb[ebn][1]=lfx1+50;
				     eb[ebn][2]=lfy+10;
				      eb[ebn][3]=1;
				     ebn++;
				      if(ebn==15)
				      ebn=0;

				     break;

				   }
			      }
			 }
		   else if(lt_dir==1)
			 {
			    for(i=0;i<5;i++)
			      {
				if(lfx1==lt_pos2[i])
				  {
				     eb[ebn][0]=lfx1;
				     eb[ebn][1]=lfx1+50;
				     eb[ebn][2]=lfy+10;
				     eb[ebn][3]=1;
				     ebn++;
				      if(ebn==15)
				      ebn=0;

				     break;

				   }
			      }
			 }

		}

		  else
		  {
		  setfillstyle(1,1);
		  bar(lfx1,lfy,lfx1+46,lfy+20);
		  lfx1=592;
		  if(lt_dir==0)
		  lt_dir=1;
		  else
		  lt_dir=0;
		  }
		 for(i=0;i<15;i++)
		   {
		       if(eb[i][3]==1)
			  {
			     eb[i][2]+=1;
			      putimage(eb[i][0],eb[i][2],enmy_bomb,COPY_PUT);
			      if(eb[i][2]+19>448)
				{
				  explode(eb[i][0],399);
				  eb[i][3]=0;
				  health=health-1;
				}
			       if((eb[i][2]+19>gy)&&(eb[i][0]>=gx1-16)&&(eb[i][0]+19<=gx1+66))
				 {
				      explode(eb[i][0]-20,382);
				      explode(gx1,gy-1);
				      eb[i][3]=0;
				      health=health-5;
				 }
			  for(j=0;j<30;j++)
			       {
				  if(gb[j][3]==1)
				    {
				     if((eb[i][2]+19>gb[j][2])&&(eb[i][0]+19>=gb[j][0]-9)&&(eb[i][0]+19<=gb[j][0]+49))
				      {
				      explode(eb[i][0]-20,eb[i][2]);
				      explode(gb[j][0]-10,gb[j][2]);
				      eb[i][3]=0;
				      gb[j][3]=0;
				      break;
				      }
				    }
				}
			       }
		   }


	       if(kbhit())
		 {
		 ch=getch();


	       if(ch==77)
	       {    for(i=0;i<10;i++)
		    {
		      if(gx1+43<639)
		      {
		     gx1=gx1+1;
		     putimage(gx1,gy,gun,COPY_PUT);
		      }
		    }
	       }
	    else if(ch==75)
	       {
		   for(i=0;i<10;i++)
		    {

		      if(gx1>1)
		     {
		     gx1=gx1-1;
		     putimage(gx1,gy,gun,COPY_PUT);
		     }
		    }
	       }

	      else if(ch==32)
		   {
		      gb[gbn][3]=1;
		      gb[gbn][0]=gx1+10;
		      gb[gbn][2]=gy-41;
		      gbn++;
		      if(gbn==30)
		      gbn=0;
		   }

		else if(ch==27)
		{
		    reset();
		    main();
		}
	     }
		     for(i=0;i<30;i++)
		   {
		       if(gb[i][3]==1)
			  {
			     gb[i][2]-=2;
			      putimage(gb[i][0],gb[i][2],gun_bomb,COPY_PUT);
			      if(gb[i][2]<2)
				{
				  explode(gb[i][0]-15,2);
				  gb[i][3]=0;

				}
			      else if((gb[i][2]-1<rfy)&&(gb[i][0]+25>=rfx1)&&(gb[i][0]-25<=rfx1))
				 {
				      explode(rfx1,rfy);
				      explode(gb[i][0],gb[i][2]);
				      gb[i][3]=0;
				      rt_flight_no=rt_flight_no-1;
				       reset1=1;

				 }
			       else if((gb[i][2]-1<lfy)&&(gb[i][0]+25>=lfx1)&&(gb[i][0]-45<=lfx1))
				 {
				      explode(lfx1,lfy);
				      explode(gb[i][0],gb[i][2]);
				      gb[i][3]=0;
				      lt_flight_no=lt_flight_no-1;
				       reset2=1;

				 }
			 }
		   }
		enmy_health=rt_flight_no+lt_flight_no;
	     setfillstyle(1,2);
	     bar(220-2*(50-health),470,220,476);
	     setfillstyle(1,2);
	     bar(598-7*(14-enmy_health),470,598,476);

	   }
  clearscreen();
ch=97;
    if(health<=0)
	{

	   i=1;
	  cleardevice();
	  setbkcolor(0);
	   setcolor(8);
	     outtextxy(250,280,"Press Enter ");
	  while(ch!='\r')
	  {
	   if(i==16)
	     i=1;
	   if(kbhit())
	     ch=getch();
	    setcolor(i);
	    delay(100);
	    settextstyle(7,0,3);
	    outtextxy(130,200,"ENEMIES WON.... Ha Ha Ha.... ");
	    i++;
	   }
	}
     else
	{
	  i=1;
	  cleardevice();
	  setbkcolor(0);
	   setcolor(8);
	     outtextxy(250,280,"Press Enter ");
	  while(ch!='\r')
	  {
	   if(i==16)
	     i=1;
	   if(kbhit())
	     ch=getch();
	    setcolor(i);
	    delay(100);
	    settextstyle(7,0,3);
	    outtextxy(70,200,"! * ! * ! * ! * YOU WON * ! * ! * ! * ! ");
	    i++;
	   }
	}

   }

/* THE BOMB WILL EXPLODE IN THE X,Y LOCATION */
void explode(int x,int y)
   {
	sound(500);
	putimage(x,y,blast,COPY_PUT);
	delay(50);
	setfillstyle(1,1);
	bar(x,y,x+50,y+50);
	setcolor(15);
	rectangle(0,0,639,479);
	putimage(gx1,gy,gun,COPY_PUT);
	nosound();
    }



main()
  {

      int gd=VGA,gm=VGAHI,maxx,maxy,x,y,button,axx,c,errorcode,area;//,y1=350;
      int select,eselect;
     //  registerbgidriver(EGAVGA_driver);
     //  registerbgifont(triplex_font);
     //  registerbgifont(gothic_font);
     //  registerbgifont(sansserif_font);
     initgraph(&gd,&gm,"");
     errorcode = graphresult();
    rectangle(0,0,639,479);
       if(errorcode!=grOk)
	{
	     printf("Graphics error: %s\n", grapherrormsg(errorcode));
	     printf("Press any key to halt:");
	     getch();
	     exit(1);
	 }
setfillstyle(1,2);
	bar(0,0,639,479);

	base();
cleardevice();

	if(initmouse()==0)
	 {
	  printf("Mouse is not initialised");
	  printf("Game can't work");
	  getch();
	 }
	      setbkcolor(0);
	 setfillstyle(1,2);
	 bar(50,50,590,420);
	  setfillstyle(1,14);
	  bar(275,100,325,120);
	  bar(275,180,325,200);
	  bar(275,260,325,280);
	  bar(275,340,325,360);
	   settextstyle(0,0,0);
	    setcolor(8);
	   outtextxy(280,107,"START");
	   outtextxy(280,187,"RULES");
	   outtextxy(285,267,"INFO");
	   outtextxy(285,347,"EXIT");
	   setcolor(7);
	   setfillstyle(1,10);
	   rectangle(67,67,222,404);
	   rectangle(55,55,234,417);
	   floodfill(60,60,7);
	   rectangle(64,64,225,407);
	   rectangle(61,61,228,410);
	   rectangle(58,58,231,413);

	   line(67,67,55,55);
	    line(222,404,234,417);
	    line(55,417,67,404);
	     line(234,55,222,67);
	   putimage(70,70,blast,COPY_PUT);
	   putimage(170,350,gun,COPY_PUT);
	   putimage(180,250,gun_bomb,COPY_PUT);
	   putimage(70,200,enmy_rt,COPY_PUT);
	   putimage(90,300,enmy_bomb,COPY_PUT);
	   putimage(170,130,enmy_lt,COPY_PUT);

	  showmouseptr();
	 restrictmouseptr(50,50,590,420);
	  while(1)
	   {
	     getmousepos(&button,&x,&y);
		if(x>=275&&x<=325&&y>=100&&y<=120)
		  {
		    setcolor(4);
		    rectangle(275,100,325,120);
		    select=1;
		    if((button &1)==1)
		     {
		       hidemouseptr();
		       restrictmouseptr(0,0,639,479);
		       cleardevice();
		       startgame();
		     }

		  }
	       else if(x>=275&&x<=325&&y>=180&&y<=200)
		  {
		    setcolor(4);
		    rectangle(275,180,325,200);
		    select=2;
		     if((button &1)==1)
		     {
			 setfillstyle(1,2);
			 bar(345,65,575,395);
		       details();
		     }

		  }
	     else if(x>=275&&x<=325&&y>=260&&y<=280)
		  {
		    setcolor(4);
		    rectangle(275,260,325,280);
		    select=3;
		    if((button &1)==1)
		     {
		       setfillstyle(1,2);
		       bar(345,65,575,395);
		       info();
		       //getmousepos();
		     }
		  }
		else if(x>=275&&x<=325&&y>=340&&y<=360)
		  {
		    setcolor(4);
		    rectangle(275,340,325,360);
		    select=4;
		     if((button &1)==1)
		     {
		       hidemouseptr();
		      cleardevice();
		     setfillstyle(1,RED);
		      setcolor(14);
		     setlinestyle(0,0,3);
		     bar(180,210,460,270);
		   rectangle(180,210,460,270);
		       showmouseptr();
		 restrictmouseptr(180,210,460,270);
		 setcolor(15);
		 outtextxy(200,220,"Are you sure you want to quit ?");
		  setfillstyle(1,11);
		  bar(240,240,280,260);
		  bar(340,240,380,260);
		  setcolor(0);
		  outtextxy(250,247,"Yes");
		  outtextxy(353,247,"No");
		  while(1)
		     {
		   getmousepos(&button,&x,&y);
		    if(x>=240&&x<=280&&y>=240&&y<=260)
		     {
		       setcolor(14);
		    rectangle(240,240,280,260);
		    eselect=1;
		     if((button &1)==1)
		     {
			 hidemouseptr();
  restrictmouseptr(0,0,639,479);
  closegraph();
  exit(1);

		     }
		     }
		    else if(x>=340&&x<=380&&y>=240&&y<=260)
		     {
		      setcolor(14);
		    rectangle(340,240,380,260);
		    eselect=2;
		     if((button &1)==1)
		     {
		       reset();
		       main();
		     }
		     }
		    else
		     {
		     switch(eselect)
		     {
		       case 1:
			 setcolor(4);
			 rectangle(240,240,280,260);
			 break;
		       case 2:
			 setcolor(4);
			 rectangle(340,240,380,260);
			 break;
		     }
		   }
		  }
		 }
		}
		else
		  {
		    switch(select)
		     {
		       case 1:
			 setcolor(14);
			 rectangle(275,100,325,120);
			 break;
		       case 2:
			 setcolor(14);
			 rectangle(275,180,325,200);
			 break;
			case 3:
			  setcolor(14);
			  rectangle(275,260,325,280);
			  break;
			case 4:
			  setcolor(14);
			  rectangle(275,340,325,360);

		     }
		  }
	     }
 /*	 getch();
	 hidemouseptr();
	restrictmouseptr(0,0,639,479);
	getch();
	closegraph();
	restorecrtmode();*/

  }


 initmouse()
    {
      ii.x.ax=0;
      int86(0x33,&ii,&oo);
      return(oo.x.ax);
     }
void  showmouseptr()
    {
     ii.x.ax=1;
     int86(0x33,&ii,&oo);
    }
void  restrictmouseptr(int x1,int y1,int x2,int y2)
    {
     ii.x.ax=7;
     ii.x.cx=x1;
     ii.x.dx=x2;
     int86(0x33,&ii,&oo);
     ii.x.ax=8;
     ii.x.cx=y1;
     ii.x.dx=y2;
     int86(0x33,&ii,&oo);
    }
void  getmousepos(int *button,int *x,int *y)
    {
     ii.x.ax=3;
     int86(0x33,&ii,&oo);
     *button=oo.x.bx;
     *x=oo.x.cx;
     *y=oo.x.dx;
     }
void  hidemouseptr()
    {
	ii.x.ax=2;
	int86(0x33,&ii,&oo);
    }



void reset()
   {
int i;
 health=50;
enmy_health=14;
rt_flight_no=7;
lt_flight_no=7;
 lt_dir=0;
rt_dir=0;
ebn=0;
gbn=0;

/* position parameters */
rfy=25;
lfy=50;
gy=400;
for(i=0;i<30;i++)
{
 gb[i][3]=0;
  if(i<15)
 eb[i][3]=0;
}
cleardevice();
  }


void details()
  {
       setcolor(4);
       setfillstyle(1,14);
       setlinestyle(1,0,3);
       bar(350,70,570,390);
       rectangle(350,70,570,390);
       setlinestyle(0,0,1);
       setcolor(9);
       settextstyle(1,0,3);
       outtextxy(420,80,"RULES");
       setcolor(0);
       settextstyle(11,0,0);
       outtextxy(360,130,"þ YOU SHOULD SAFEGAURD ");
       outtextxy(360,140,"  YOUR PORT WALL ");
       outtextxy(360,150,"þ ENEMY PLANES WILL ");
       outtextxy(360,160,"  ATTACK YOU ");
       outtextxy(360,170,"þ YOU CAN ADJUST YOUR ");
       outtextxy(360,180,"  GUN USING ARROW KEYS ");
       outtextxy(360,190,"þ IF ENEMY BOMBS BOMBARD ");
       outtextxy(360,200,"  WITH YOUR WALL,YOU WILL ");
       outtextxy(360,210,"  LOSE LESS POINTS ");
       outtextxy(360,220,"þ IF IT HITS THE GUN,YOU ");
       outtextxy(360,230,"  WILL LOSE MANY POINTS");
       outtextxy(360,240,"þ YOU CAN ATTACK THE  ");
       outtextxy(360,250,"  PLANES BY PRESSING ");
       outtextxy(360,260,"  |SPACE| BUTTON  ");
       outtextxy(360,270,"þ YOUR CHANCE OF WINNING ");
       outtextxy(360,280,"  DEPENDS ON NUMBER OF ");
       outtextxy(360,290,"  ENEMY PLANES HIT");
       outtextxy(360,300,"þ YOUR STRENGTH AND  ");
       outtextxy(360,310,"  ENEMIES STRENGTH ARE ");
       outtextxy(360,320,"  SHOWN AT THE BOTTOM");
       setcolor(2);
       settextstyle(6,0,1);
       outtextxy(360,340,"  * ENJOY THE GAME *");
      }

void info()
  {
       setcolor(4);
       setfillstyle(1,14);
       setlinestyle(1,0,3);
       bar(350,70,570,290);
       rectangle(350,70,570,290);
       setlinestyle(0,0,1);
       setcolor(9);
       settextstyle(1,0,3);
       outtextxy(390,80,"INFORMATION");
       setcolor(0);
       settextstyle(11,0,0);
       outtextxy(360,130,"Created by :  ");
       setcolor(8);
       outtextxy(360,150,"  Senthilnathan, A (meetsenthilnathan@gmail.com), IInd year B.tech,CSE");
       outtextxy(360,160,"  Sri Manakula Vinayagar ");
       outtextxy(360,170,"  Engineering College ");
       outtextxy(360,180,"  Puducherry  ");
       setcolor(0);
       outtextxy(360,200,"Date :  ");
       setcolor(8);
       outtextxy(360,210,"  22/JUL/2007 ");
       setcolor(0);
       outtextxy(360,230,"Language Used : ");
       setcolor(8);
       outtextxy(490,230,"  C ");
       
  }
