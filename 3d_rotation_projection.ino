//Include the graphics library.
#include "U8glib.h" 
//Initialize display.
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);

#define SCR_WDT 128
#define SCR_HGT 64

const int SCR_CEN_X = SCR_WDT / 2;
const int SCR_CEN_Y = SCR_HGT / 2;

void setup(void)
{
}
int theta = 0;
float rot_x [3][3] =  {
    {1.0, 0.0, 0.0},
    {0.0, cos(radians(theta)), -sin(radians(theta))},
    {0.0, sin(radians(theta)), cos(radians(theta))}
};

float rot_y [3][3] =  {
    {cos(radians(theta)), 0.0, sin(radians(theta))},
    {0.0, 1.0, 0.0},
    {-sin(radians(theta)),  cos(radians(theta)), 0.0}
    
};

float rot_z [3][3] =  {
    {cos(radians(theta)), 0.0, sin(radians(theta))},
    {0.0, 1.0, 0.0},
    {-sin(radians(theta)), cos(radians(theta)), 0.0}
};

void modify_rot_x (){
    rot_x[1][1] = cos(radians(theta));
    rot_x[1][2] = -sin(radians(theta));
    rot_x[2][1] = sin(radians(theta));
    rot_x[2][2] = cos(radians(theta));
}
void modify_rot_y (){
    rot_y[0][0] = cos(radians(theta));
    rot_y[0][2] = sin(radians(theta));
    rot_y[2][0] = -sin(radians(theta));
    rot_y[2][1] = cos(radians(theta));
}
void modify_rot_z (){
    rot_z[0][0] = cos(radians(theta));
    rot_z[0][1] = -sin(radians(theta));
    rot_z[1][0] = sin(radians(theta));
    rot_z[1][1] = cos(radians(theta));   
}


// Edit MACROs here, according to your Matrix Dimensions for
// mat1[R1][C1] and mat2[R2][C2]
#define R1 3 // number of rows in Matrix-1
#define C1 3 // number of columns in Matrix-1
#define R2 3 // number of rows in Matrix-2
#define C2 1 // number of columns in Matrix-2


float rslt[R1];
void mulMat_3x3_3x1(float mat1[][C1], float mat2[R2]){
    for (int t = 0; t < R1; t++)
        rslt[t] = 0.0;
    for (int i = 0; i < R1; i++) {
        for (int j = 0; j < C2; j++) {
            rslt[i] = 0.0;
            for (int k = 0; k < R2; k++) {
                rslt[i] += mat1[i][k] * mat2[k];
            }
        }
    }
}

int SCALE = 15;
float points_3d [8][3] = {  // eight 3D points - set values for 3D cube
{-1.0, -1.0, 1.0},
{1.0, -1.0, 1.0},
{1.0, 1.0, 1.0},
{-1.0, 1.0, 1.0},

{-1.0, -1.0, -1.0},
{1.0, -1.0, -1.0},
{1.0, 1.0, -1.0},
{-1.0, 1.0, -1.0},
};

float projection_m[3][3] ={
{1.0, 0.0, 0.0},
{0.0, 1.0, 0.0},
{0.0, 0.0, 0.0}  
};

int finalpoints2D [8][2] = {0};

void loop(void)
{
    u8g.firstPage();
    do {
        for(int i=0; i<8;i++){
            float points_vec[3] = {points_3d[i][0], points_3d[i][1], points_3d[i][2]};
            mulMat_3x3_3x1(rot_x, points_vec);
            float rotated3d[3];
            for(int i=0; i<3; i++){
                rotated3d[i] = rslt[i];
            }
            mulMat_3x3_3x1(rot_y, rotated3d);
            for(int i=0; i<3; i++){
                rotated3d[i] = rslt[i];
            }
            mulMat_3x3_3x1(projection_m, rotated3d);
            float projected_2d[3];
            for(int i=0; i<3; i++){
                projected_2d[i] = rslt[i];
            }
            finalpoints2D[i][0] = projected_2d[0]*SCALE+SCR_CEN_X;
            finalpoints2D[i][1] = projected_2d[1]*SCALE+SCR_CEN_Y;
            //u8g.drawPixel(projected_2d[0]*SCALE+SCR_CEN_X, projected_2d[1]*SCALE+SCR_CEN_Y);
            
        }
        u8g.drawLine(finalpoints2D[0][0], finalpoints2D[0][1], finalpoints2D[1][0], finalpoints2D[1][1]);
        u8g.drawLine(finalpoints2D[1][0], finalpoints2D[1][1], finalpoints2D[2][0], finalpoints2D[2][1]);
        u8g.drawLine(finalpoints2D[2][0], finalpoints2D[2][1], finalpoints2D[3][0], finalpoints2D[3][1]);
        u8g.drawLine(finalpoints2D[3][0], finalpoints2D[3][1], finalpoints2D[0][0], finalpoints2D[0][1]);
        u8g.drawLine(finalpoints2D[4][0], finalpoints2D[4][1], finalpoints2D[5][0], finalpoints2D[5][1]);
        u8g.drawLine(finalpoints2D[5][0], finalpoints2D[5][1], finalpoints2D[6][0], finalpoints2D[6][1]);
        u8g.drawLine(finalpoints2D[6][0], finalpoints2D[6][1], finalpoints2D[7][0], finalpoints2D[7][1]);
        u8g.drawLine(finalpoints2D[7][0], finalpoints2D[7][1], finalpoints2D[4][0], finalpoints2D[4][1]);
        u8g.drawLine(finalpoints2D[0][0], finalpoints2D[0][1], finalpoints2D[4][0], finalpoints2D[4][1]);
        u8g.drawLine(finalpoints2D[1][0], finalpoints2D[1][1], finalpoints2D[5][0], finalpoints2D[5][1]);
        u8g.drawLine(finalpoints2D[3][0], finalpoints2D[3][1], finalpoints2D[7][0], finalpoints2D[7][1]);
        u8g.drawLine(finalpoints2D[2][0], finalpoints2D[2][1], finalpoints2D[6][0], finalpoints2D[6][1]);
        theta++;
        modify_rot_x();
        modify_rot_y();
    } while (u8g.nextPage());
}

