//Drawbacks of DDA Algorithm : DDA was generating the point in floating numher values like 2.345 , 6,09234 
//- but we need the point in rounded numbers like 2,3,4,etc
// slope (m) = (y2-y1) / (x2-x1)
// Decision Paramter (p) =  2 (y2-y1) - (x2-x1)
// if m <1 
	// if p<0
		// x(i+1) = x(i) + 1 
		// y (i+1) = y(i)
		//  p(k+1) = p(k) + 2 (y2-y1)
	// else if   p>=0
		// x(i+1) = x(i) + 1 
		// y (i+1) = y(i) + 1 
		//  p(k+1) = p(k) + 2 (y2-y1) - 2 (x2-x1)
//  else if m >=1
	// if p<0
		// x(i+1) = x(i) 
		// y (i+1) = y(i) +1
		//  p(k+1) = p(k) + 2 (x2-x1)
	// else if   p>=0
		// x(i+1) = x(i) + 1 
		// y (i+1) = y(i) + 1 
		//  p(k+1) = p(k) +  2 (x2-x1) -2 (y2-y1) 
// breshname algorithm used in this program
// step 1 : calculate delta x and delta y 
// step 2 : decision parameter P(k) = 2delta y - delta x
// step 3 : if P(k) is less than zero : Pk+1 = Pk + 2 delta y
			// 							X(k+1) = X(k) +1
			// 							Y(k+1) = Y(k)
			 // if P(k) is greater than zero : Pk+1 = Pk + 2 delta y -  delta x
			// 							X(k+1) = X(k) +1
			// 							Y(k+1) = Y(k)  +1 
// step 4 : repeat step 4 untill the end point is reached
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream> 
#define h 500
#define w 500
#include<math.h>
using namespace std;
int a1,b2,c1,d2;
void myInit(void){

	glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
  glColor3f(1.0f,1.0f,0.0f);
	glLineWidth(5.0);
	glPointSize(3.0);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w/2, w/2, -h/2, h/2);
}

void setPixel(int x, int y){
	glColor3f(1.0f, 1.0f, 0.1f);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	
}


void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	  for (int i = -w; i < w; i++){
		setPixel(i, 0);
		setPixel(0, i);    
    }
	glFlush();
}

  void Line(int x1,int y1,int x2,int y2){
    
   	glBegin(GL_POINTS); 
   		glColor3f(1.0f, 0.0f, 0.1f);
   		glPointSize(3.0);
	int dx,dy,p; 
     x1=a1;
     y1=b2;
     //calculating delta x and delta y and decision parameter (1 & 2 )
     dx=x2-x1;
     dy=y2-y1;
     p=2*dx-dy;
     int i=1;
     while(x1<=x2){ // until we reach the endpoint (4)
      	glVertex2f(x1,y1); //keep plotting x1 and y1
     	x1=x1+1; // adding one to the x common for both the cases
     	if(p<0){
     		p=p+2*dy; // calculating p while keeping y the same that's why y is not specified  (3)( case 01 )
     		
		 }
		 else{
		 	p=p+2*dy-dx; // calculating p 
		 	y1=y1+1; //adding 1 to the y according to the formula (3)( case 02 )
		 }
	 }

     
	     glEnd();
 	glFlush();
	 
 }

 void dashed_Line(int x1,int y1,int x2,int y2){ 
   	glBegin(GL_POINTS); 
   		glColor3f(1.0f, 0.0f, 0.1f);
   		glPointSize(3.0);
	int dx,dy,p; 
     x1=a1;
     y1=b2;
     dx=x2-x1;
     dy=y2-y1;
     p=2*dx-dy;
     int i=1;
     while(x1<=x2){
    if(i%10>=4){ // only plotting for points like 4,5,6,7,8,9 etc to keep smaller gap (closer points)
     		glVertex2f(x1,y1);
		 }
		 i++;
   //implementation is same as specified above
     	x1=x1+1;
     	if(p<0){
     		p=p+2*dy;
     		
		 }
		 else{
		 	p=p+2*dy-dx;
		 	y1=y1+1;
		 }
	 }

     
	     glEnd();
 	glFlush();
	 
 }
  
   void dotted_Line(int x1,int y1,int x2,int y2){
    
   	glBegin(GL_POINTS); 
   		glColor3f(1.0f, 0.0f, 0.1f);
   		glPointSize(3.0);
	int dx,dy,p; 
     x1=a1;
     y1=b2;
     dx=x2-x1;
     dy=y2-y1;
     p=2*dx-dy;
     int i=1;
     while(x1<=x2){
    if(i%3==0){ // only plotting for points like 3,6,9,12,15,18,21,24,27,30,33 etc to keep a bit larger gap (a bit far away points)
     		glVertex2f(x1,y1);
		 }
		 i++;
  //process is same as that of explained in the normal line function 
     	x1=x1+1;
     	if(p<0){
     		p=p+2*dy;
     		
		 }
		 else{
		 	p=p+2*dy-dx;
		 	y1=y1+1;
		 }
	 }

	     glEnd();
 	glFlush();
	 
 }


 void menu(int choice){

        if(choice==1){
               Line(a1,b2,c1,d2);
        }
        else if(choice==2){
                dashed_Line(a1,b2,c1,d2);
        }
        else if(choice==3){
                dotted_Line(a1,b2,c1,d2);
        }
        else if(choice==4){
        	//program will be terminated
                exit(0);
        }
}


int main(int argc, char** argv) {
	// taking  co-ordinates fro users and storing them in global scope
	cout<<"enter first coordinates=";
	cin>>a1;
	cin>>b2;
	cout<<endl;
	cout<<"enter second coordinates=";
	cin>>c1;
	cin>>d2;
	cout<<endl;
	
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Breshnam's Line Drawing Algorithm");
    
    glutDisplayFunc(myDisplay);
      glutCreateMenu(menu);
          glutAddMenuEntry("Simple Line ",1);
          glutAddMenuEntry("Dotted Line ",3);
          glutAddMenuEntry("Dashed Line ",2);
          glutAddMenuEntry("Exit ",4);
         
         glutAttachMenu(GLUT_RIGHT_BUTTON);
    myInit();
    glutMainLoop();
	return 0;
}
