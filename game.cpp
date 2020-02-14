#include "game.h"

int main(int argc, char **argv) {
  glutInit(&argc, argv); // Initialize GLUT
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // Set up double buffering, rgba and depth
  glutInitWindowSize (600, 600);     // Set the width and height of the window
  glutInitWindowPosition (100, 100); // Set the position of the window
  glutCreateWindow ("VraXaPsa III"); // Set the title for the window

  init();
  createGLUTMenus();        // Create the game menu
  glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering
  glutIdleFunc(idle);       // Tell GLUT to use the method "display" as our idle method as well
  glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for rendering

  glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses
  glutSpecialFunc(keySpecial);  // Tell GLUT to use the method "keySpecial" for special key presses
  glutMainLoop();
}


void init(void) {
  glClearColor(0.f, 0.f, 0.f, 1.f); // Clear the background of our window to black
  glEnable(GL_BLEND);               // Enable the OpenGL Blending functionality
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set the blend mode to blend our current RGBA with what is already in the buffer
  glClearDepth(1);
  glEnable(GL_DEPTH_TEST);         // Enable depth
  glEnable(GL_LIGHTING);           // Enable lighting
  glEnable(GL_LIGHT0);             // Choose lighting type
  glEnable(GL_COLOR_MATERIAL);     // Make lighting interact with our colours
  glShadeModel (GL_SMOOTH);        // Set the shader to smooth shader
}


void idle() {
  glutPostRedisplay();   // Post a re-paint request to activate display()
}


void display() {
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the colour buffer and the depth buffer
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();     // Load the Identity Matrix to reset our drawing locations
  camera();
  renderPrimitive();    // Render the primitive
  glutSwapBuffers();    // Swap our buffers
  angle++;              // Increase the angle
}


void reshape(int width, int height){
  glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
  glMatrixMode(GL_PROJECTION);                       // Switch to the projection matrix so that we can manipulate how our scene is viewed
  glLoadIdentity();                                  // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
  gluPerspective(45, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
  glMatrixMode(GL_MODELVIEW);                        // Switch back to the model view matrix, so that we can start drawing shapes correctly
}


void keyPressed(unsigned char key, int x, int y) {
  if (key==27){    // ESC
   exit(0);
  }
}


void keySpecial(int key, int x, int y) {
  if (key==GLUT_KEY_F1){   // ZOOM OUT
     float xrotrad, yrotrad;
     yrotrad = (yrot / 180 * 3.141592654f);
     xrotrad = (xrot / 180 * 3.141592654f);
     xpos -= float(sin(yrotrad));
     zpos += float(cos(yrotrad)) ;
     ypos += float(sin(xrotrad));
  }
  if (key==GLUT_KEY_F2){   // ZOUM IN
     float xrotrad, yrotrad;
     yrotrad = (yrot / 180 * 3.141592654f);
     xrotrad = (xrot / 180 * 3.141592654f);
     xpos += float(sin(yrotrad)) ;
     zpos -= float(cos(yrotrad)) ;
     ypos -= float(sin(xrotrad)) ;
  }
  if (key==GLUT_KEY_LEFT){
     yrot -= 1;
     if (yrot < -360)yrot += 360;
  }
  if (key==GLUT_KEY_RIGHT){
     yrot += 1;
     if (yrot >360) yrot -= 360;
  }
  if (key==GLUT_KEY_DOWN){
      xrot += 1;
      if (xrot >360) xrot -= 360;
  }
  if (key==GLUT_KEY_UP){
      xrot -= 1;
      if (xrot < -360) xrot += 360;
  }
  if (key==GLUT_KEY_F4){
      cameraReset();
  }
}


void camera () {
  glRotatef(xrot,1.0,0.0,0.0);     // rotate our camera on the x-axis (left and right)
  glRotatef(yrot,0.0,1.0,0.0);     // rotate our camera on the y-axis (up and down)
  glTranslated(-xpos,-ypos,-zpos); // translate the screen to the position of our camera
}


void cameraReset(){               // resets the Camera to the original view
  xrot=0;
  yrot=0;
  ypos=0;
  xpos=0;
  zpos=0;
  angle=0.0;
}


void renderPrimitive() {        // Create the starter 15x15 cube grid
  float i;
  float j;
  for(i=-7.0; i<=7.0; i=i+1) {
    for(j=-7.0; j<=7.0; j=j+1) {
      glPushMatrix();
      glColor3f(0.9f, 0.9f, 0.7f);
      glTranslatef(i, j, -22.0);
      glutSolidCube(0.7);
      glPopMatrix();
    }
  }
}


void createGLUTMenus() {
  int menu;                            // create the menu and tell glut that "processMenuEvents" will handle the events
  menu = glutCreateMenu(processMenuEvents);
  glutAddMenuEntry("Start Game",1);    //add entries to our menu
  glutAddMenuEntry("Exit",0);
  glutAttachMenu(GLUT_RIGHT_BUTTON);   // attach the menu to the right button
}


void processMenuEvents(int option) {
  switch (option) {
    case 0 :  // Option 1: Exit
        exit(0);
        break;
    case 1 :  // Option 2: Start Game
        cameraReset();                // with every new game camera resets
        srand(time(0));               // Uses a time seed to make sure that every time we get a different colored grid
        initializeGrid();
		glutDisplayFunc(replace);     // change the display from renderPrimitive to replace
		glutPostRedisplay();
        globalMouseCounter = 1;
        moves = 30;                   // with new game moves and score refreshes
        score =0;
        break;
  }
  return;
}


void mouseControl(int button, int state, int x, int y){       // take the X and Y from mouse left click
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    std::cout << x << "," << y << " , ";
    std::cout << '\n';
    if(globalMouseCounter == 1){
      select1(x, y);
      globalMouseCounter = 2;
    }else if(globalMouseCounter == 2){
      select2(x, y);
      doTheSwap(selectedSecond.cubeX , selectedSecond.cubeY);
      globalMouseCounter = 1;
    }
  }
}


void select1(int x , int y) {                        // selects First shape for swap
  int n = 0 , m=0, k=x, l=y;
  int i,j;

  for(i=xStart; i<=xEnd; i=i+33) {
    if(k >= (i+33)) {
      n = n + 1;
    }
  }
  for(j=yStart; j>=yEnd; j=j-33) {
    if(l <= (j-33)){
      m = m + 1;
    }
  }
  if(x >= (xStart + n*(cubeSize+spaceSize)) && x <= (xStart + n*(cubeSize+spaceSize) + cubeSize) && x <= xEnd) {
    if(y <= (yStart - m*(cubeSize+spaceSize)) && y >= (yStart - m*(cubeSize+spaceSize) - cubeSize) && y >= yEnd) {
      selectedFirst.cubeX = n;
      selectedFirst.cubeY = m;
      selectedFirst.color = grid[n][m].color;
    }
  }
}


void select2(int x , int y) {                      // selects Second shape for swap
  int n = 0 , m=0, k=x, l=y;
  int i,j;

  for(i=xStart; i<=xEnd; i=i+33) {
    if(k >= (i+33)) {
      n = n + 1;
    }
  }
  for(j=yStart; j>=yEnd; j=j-33) {
    if(l <= (j-33)){
      m = m + 1;
    }
  }
  if(x >= (xStart + n*(cubeSize+spaceSize)) && x <= (xStart + n*(cubeSize+spaceSize) + cubeSize) && x <= xEnd) {
    if(y <= (yStart - m*(cubeSize+spaceSize)) && y >= (yStart - m*(cubeSize+spaceSize) - cubeSize) && y >= yEnd) {
      selectedSecond.cubeX = n;
      selectedSecond.cubeY = m;
      selectedSecond.color = grid[n][m].color;
    }
  }
}


void doTheSwap(int x, int y) {                    // swaps the shapes from select1 and select2
  int tempx, tempy, tempc;

  tempx = selectedFirst.cubeX;
  tempy = selectedFirst.cubeY;
  tempc = selectedFirst.color;
  if(!(selectedFirst.cubeX == selectedSecond.cubeX && selectedFirst.cubeY == selectedSecond.cubeY) &&      // cannot swap the same cube
     !(selectedFirst.cubeX != selectedSecond.cubeX && selectedFirst.cubeY != selectedSecond.cubeY) &&      // cannot swap diagonal cubes
     (selectedSecond.cubeX >= selectedFirst.cubeX -1 && selectedSecond.cubeX <= selectedFirst.cubeX +1) && // the cube to be swaped must be adjascent on X axis
     (selectedSecond.cubeY >= selectedFirst.cubeY -1 && selectedSecond.cubeY <= selectedFirst.cubeY +1) && // the cube to be swaped must be adjascent on Y axis
     (selectedFirst.color != selectedSecond.color) &&                                                      // cannot swap cubes of the same color
     (moves > 0)){ // There must be moves left
    grid[selectedFirst.cubeX][selectedFirst.cubeY] = grid[x][y];
    grid[x][y] = grid[tempx][tempy];
    grid[x][y].color = tempc;
    moves--;
    check(x, y);
    if (grid[x][y].color!=0){     //Not scoring black boxes.
      destroy(counterLeft, counterRight, counterBottom, counterTop, x, y);
    }
    check(tempx, tempy);
    if (grid[tempx][tempy].color!=0){
      destroy(counterLeft, counterRight, counterBottom, counterTop, x, y);
    }
  }
}


// Checks how many continueous neighbour shapes
void check(int x, int y) {
  int i;
  counterRight = 0, counterLeft = 0;
  counterBottom = 0,  counterTop = 0;
  for(i=x; i<=14; i++){ //check for x axis right
    if(grid[i][y].color != grid[i+1][y].color) {
      counterRight = i;
      break;
    }
  }
  for(i=x; i>=0; i--){ // check for x axis left
    if(grid[i][y].color != grid[i-1][y].color) {
      counterLeft = i;
      break;
    }
  }
  for(i=y; i>=0; i--){ // check for y axis down
    if(grid[x][i].color != grid[x][i-1].color) {
      counterBottom = i;
      break;
    }
  }
  for(i=y; i<=14; i++){ // check for y axis down
    if(grid[x][i].color != grid[x][i+1].color) {
      counterTop = i;
      break;
    }
  }
}


//destroys the n-sized same color groups
void destroy(int counterLeft, int counterRight, int counterBottom, int counterTop, int x, int y) {
  int destroyedBoxes = 0;

  if((counterRight - counterLeft) >= 2) {
    for(int i=counterLeft; i<= counterRight; i++){
      grid[i][y].color = 0;
      //if (!(grid))
        destroyedBoxes++;
    }
  }

  if((counterTop-counterBottom) >= 2) {
    for(int i=counterBottom; i<=counterTop; i++){
      grid[x][i].color = 0;
      destroyedBoxes++;
    }
  }
  score += 10*destroyedBoxes; // every destryed box values for 10 poins.
}                             // if you score a corner group you earn 10 extra points.


void replace() {
  glClearColor(0.f, 0.f, 0.f, 1.f);                    // Clear the background of our window to black
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the colour buffer and the depth buffer
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();  // Load the Identity Matrix to reset our drawing locations
  glutMouseFunc(mouseControl);
  angle++; //increase the angle

  // score
  char text[20] = "Score: ";
  char StringPoints[100];
  sprintf(StringPoints, "%d", score);
  strcat(text, StringPoints);
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  drawText(600, 720, text);

  // moves
  if (moves!=0){
    char text2[20] = "Moves: ";
    char StringMoves[100];
    sprintf(StringMoves, "%d", moves);
	  strcat(text2, StringMoves);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  	drawText(100, 720, text2);
  }

  // game over
  if (moves==0){
    char text3[20] = "GAME OVER";
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    drawText(310, 720, text3);
  }


  int i;
  int j;
  for(i=-7.0; i<=7.0; i=i+1) {
    for(j=-7.0; j<=7.0; j=j+1) {
      glPushMatrix();
      camera();
      glTranslatef(i, j, -22.0);

      if ( grid[i+7][j+7].color == 0){          // 0 black CUBE
        glColor3f(0.0f, 0.0f, 0.0f);
        glutSolidCube(0.7);

      }else if ( grid[i+7][j+7].color == 1){    // 1 blue CUBE
        glColor3f(0.0f, 0.0f, 1.0f);
        glutSolidCube(0.7);

      }else if ( grid[i+7][j+7].color == 2){    // 2 red CUBE
        glColor3f(1.0f, 0.0f, 0.0f);
        glutSolidCube(0.7);

      }else if ( grid[i+7][j+7].color == 3){    // 3 green Cone (psalidi)
        glColor3f(0.0f, 1.0f, 0.0f);
        glutSolidCone(0.5,0.7,4,15);

      }else if ( grid[i+7][j+7].color == 4){    // 4 yellow BALL (vraxos)
        glColor3f(1.0f, 1.0f, 0.0f);
        glutSolidSphere(0.46,30,30);

      }else{                                    // 5 purple DONUT (xarti)
        glColor3f(1.0f, 0.0f, 1.0f);
        glutSolidTorus(0.17,0.3,25,25);
      }
      glPopMatrix();
    }
  }
  glutSwapBuffers();
}

//screen text
void drawText(int x, int y, char *string) {
	char *c;
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 780, 0, 780, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);

}

// the grid that interacts with the objects
void initializeGrid(){
  int i;
  int j;
  for(i=0; i<15; i=i+1) {
    for(j=0; j<15; j=j+1) {
      grid[i][j].color = (rand()%5)+1;
      grid[i][j].cubeX = i;
      grid[i][j].cubeY = j;
      std::cout << grid[i][j].color<<" , ";
    }
    std::cout << '\n';
  }
}
