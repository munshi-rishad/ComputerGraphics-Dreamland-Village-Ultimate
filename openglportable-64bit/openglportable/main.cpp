#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#define PI 3.14159265358979323846

int sceneMode = 0;
bool introScreen = true;
bool musicOn = true;
bool showHelp = true;
bool houseLights = true;
bool boatMoving = true;
bool fullScreen = false;
float cloudOffsetA = 0.0f;
float cloudOffsetB = 0.0f;
float birdOffset = 0.0f;
float wingPhase = 0.0f;
float riverPhase = 0.0f;
float reflectionPhase = 0.0f;
float boatX = 0.0f;
int boatDirection = 1;
float duckOffset = 0.0f;
float fishPhase = 0.0f;
float smokePhase = 0.0f;
float clothPhase = 0.0f;
float fireflyPhase = 0.0f;
float rainX[260];
float rainY[260];
int lightningTimer = 0;

float palmPhase = 0.0f;
float bananaPhase = 0.0f;
int cowDirection = 1;
float cowX = 14.0f;
float cowLegPhase = 0.0f;

float chickenX = 24.0f;
float chickenWalkPhase = 0.0f;

float cowTailPhase = 0.0f;
float flowerPhase = 0.0f;
float fieldPhase = 0.0f;
float fishSwim = 0.0f;

float sunRayPhase = 0.0f;
float grassPhase = 0.0f;
float ripplePhase = 0.0f;
float starTwinklePhase = 0.0f;
float rainSplashPhase = 0.0f;
float oarPhase = 0.0f;
typedef BOOL (WINAPI *PlaySoundAFunc)(LPCSTR, HMODULE, DWORD);
PlaySoundAFunc getPlaySoundFunction()
{
    static HMODULE winmm = LoadLibraryA("winmm.dll");
    static PlaySoundAFunc playSoundA = NULL;
    if (winmm != NULL && playSoundA == NULL)
    {
        playSoundA =
            (PlaySoundAFunc)GetProcAddress(winmm, "PlaySoundA");
    }
    return playSoundA;
}
void stopSound()
{
    PlaySoundAFunc playSoundA = getPlaySoundFunction();
    if (playSoundA != NULL)
    {
        playSoundA(NULL, NULL, 0);
    }
}
void playLoopSound(const char* fileName)
{
    if (!musicOn)
        return;
    PlaySoundAFunc playSoundA = getPlaySoundFunction();
    if (playSoundA != NULL)
    {
        const DWORD SND_ASYNC_FLAG = 0x0001;
        const DWORD SND_LOOP_FLAG = 0x0008;
        const DWORD SND_FILENAME_FLAG = 0x00020000;
        playSoundA(
            fileName,
            NULL,
            SND_ASYNC_FLAG |
            SND_LOOP_FLAG |
            SND_FILENAME_FLAG
        );
    }
}
void updateSound();
void resumeSceneSound(int)
{
    if (musicOn)
        updateSound();
}
void cowSoundTimer(int)
{
    if (!introScreen && musicOn && (sceneMode == 0 || sceneMode == 1))
    {
        PlaySoundAFunc playSoundA = getPlaySoundFunction();
        if (playSoundA != NULL)
        {
            const DWORD SND_ASYNC_FLAG = 0x0001;
            const DWORD SND_FILENAME_FLAG = 0x00020000;
            playSoundA(
                "cow.wav",
                NULL,
                SND_ASYNC_FLAG | SND_FILENAME_FLAG
            );
            glutTimerFunc(2000, resumeSceneSound, 0);
        }
    }
    glutTimerFunc(10000, cowSoundTimer, 0);
}
void updateSound()
{
    stopSound();
    if (!musicOn)
        return;
    if (sceneMode == 3)
        playLoopSound("rain.wav");
    else if (sceneMode == 2)
        playLoopSound("night.wav");
    else
        playLoopSound("nature.wav");
}
void rect(float x1, float y1, float x2, float y2)
{
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}
void circle(float cx, float cy, float r, int parts = 70)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < parts; i++)
    {
        float a = 2.0f * PI * i / parts;
        glVertex2f(
            cx + cos(a) * r,
            cy + sin(a) * r
        );
    }
    glEnd();
}
void ellipse(float cx, float cy, float rx, float ry, int parts = 70)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < parts; i++)
    {
        float a = 2.0f * PI * i / parts;
        glVertex2f(
            cx + cos(a) * rx,
            cy + sin(a) * ry
        );
    }
    glEnd();
}
void line(float x1, float y1, float x2, float y2, float width = 1.0f)
{
    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}
void drawText(float x, float y, const char* text, void* font)
{
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(font, text[i]);
    }
}
void drawIntro()
{
    glClearColor(0.03f, 0.08f, 0.16f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glColor3f(0.04f, 0.18f, 0.36f);
    glVertex2f(0, 80);
    glVertex2f(100, 80);
    glColor3f(0.16f, 0.62f, 0.78f);
    glVertex2f(100, 0);
    glVertex2f(0, 0);
    glEnd();
    glColor3f(1.0f, 0.88f, 0.55f);
    circle(82, 66, 5);
    glColor3f(0.04f, 0.18f, 0.36f);
    circle(84, 67, 4.6f);
    glColor3f(0.08f, 0.42f, 0.18f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 22);
    glVertex2f(18, 25);
    glVertex2f(36, 22);
    glVertex2f(55, 26);
    glVertex2f(72, 23);
    glVertex2f(100, 27);
    glVertex2f(100, 0);
    glVertex2f(0, 0);
    glEnd();
    glColor3f(0.12f, 0.08f, 0.05f);
    rect(68, 14, 82, 25);
    glBegin(GL_TRIANGLES);
    glVertex2f(65, 25);
    glVertex2f(75, 34);
    glVertex2f(85, 25);
    glEnd();
    glColor3f(1.0f, 0.82f, 0.22f);
    drawText(
        30,
        55,
        "DREAMLAND VILLAGE ULTIMATE",
        GLUT_BITMAP_TIMES_ROMAN_24
    );
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(
        33,
        48,
        "A NEW INTERACTIVE OPENGL VILLAGE",
        GLUT_BITMAP_HELVETICA_18
    );
    drawText(
        38,
        40,
        "PRESS ENTER TO START",
        GLUT_BITMAP_HELVETICA_18
    );
    glColor3f(0.86f, 0.94f, 1.0f);
    drawText(
        31,
        33,
        "Day | Sunset | Night | Rain | Sound | Animation",
        GLUT_BITMAP_HELVETICA_12
    );
    glutSwapBuffers();
}
void drawSky()
{
    glBegin(GL_QUADS);
    if (sceneMode == 0)
        glColor3f(0.08f, 0.52f, 0.95f);
    else if (sceneMode == 1)
        glColor3f(0.42f, 0.10f, 0.40f);
    else if (sceneMode == 2)
        glColor3f(0.01f, 0.03f, 0.12f);
    else
        glColor3f(0.16f, 0.24f, 0.34f);
    glVertex2f(0, 80);
    glVertex2f(100, 80);
    if (sceneMode == 0)
        glColor3f(0.65f, 0.90f, 1.0f);
    else if (sceneMode == 1)
        glColor3f(1.0f, 0.42f, 0.16f);
    else if (sceneMode == 2)
        glColor3f(0.04f, 0.08f, 0.22f);
    else
        glColor3f(0.38f, 0.48f, 0.58f);
    glVertex2f(100, 38);
    glVertex2f(0, 38);
    glEnd();
}
void drawSunMoonStars()
{
    if (sceneMode == 0)
    {
        glColor3f(1.0f, 0.68f, 0.06f);
        circle(18, 69, 4.5f);
    }
    else if (sceneMode == 1)
    {
        glColor3f(1.0f, 0.22f, 0.03f);
        circle(76, 47, 5.0f);
    }
    else if (sceneMode == 2)
    {
        glColor3f(1.0f, 0.95f, 0.68f);
        circle(82, 69, 4.1f);
        glColor3f(0.04f, 0.08f, 0.22f);
        circle(84, 70, 3.8f);
        glColor3f(1.0f, 1.0f, 0.90f);
        glPointSize(2.0f);
        glBegin(GL_POINTS);
        glVertex2f(6, 74);
        glVertex2f(12, 65);
        glVertex2f(20, 73);
        glVertex2f(27, 77);
        glVertex2f(34, 68);
        glVertex2f(40, 75);
        glVertex2f(48, 64);
        glVertex2f(55, 76);
        glVertex2f(63, 70);
        glVertex2f(70, 75);
        glVertex2f(90, 76);
        glVertex2f(95, 67);
        glVertex2f(98, 74);
        glEnd();
    }
}
void drawSunRays()
{
    if (sceneMode != 0)
        return;

    glPushMatrix();
    glTranslatef(18.0f, 69.0f, 0.0f);
    glRotatef(sunRayPhase, 0.0f, 0.0f, 1.0f);

    glColor3f(1.0f, 0.76f, 0.08f);
    for (int i = 0; i < 12; i++)
    {
        float a = (2.0f * PI * i) / 12.0f;
        float x1 = cos(a) * 5.7f;
        float y1 = sin(a) * 5.7f;
        float x2 = cos(a) * 7.2f;
        float y2 = sin(a) * 7.2f;
        line(x1, y1, x2, y2, 1.2f);
    }

    glPopMatrix();
}

void drawGrassDetails()
{
    if (sceneMode == 2)
        glColor3f(0.05f, 0.25f, 0.06f);
    else
        glColor3f(0.08f, 0.42f, 0.08f);

    for (int i = 0; i < 18; i++)
    {
        float x = 2.0f + i * 5.5f;
        float y = 17.5f + (i % 3) * 0.7f;
        float sway = sin(grassPhase + i * 0.6f) * 0.35f;

        line(x, y, x - 0.5f + sway, y + 1.7f, 1.0f);
        line(x, y, x + sway, y + 2.0f, 1.0f);
        line(x, y, x + 0.5f + sway, y + 1.5f, 1.0f);
    }
}

void drawRipple(float cx, float cy, float rx, float ry)
{
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 36; i++)
    {
        float a = 2.0f * PI * i / 36.0f;
        glVertex2f(cx + cos(a) * rx, cy + sin(a) * ry);
    }
    glEnd();
}

void drawRiverRipples()
{
    if (sceneMode == 3)
        return;

    float p = 0.35f + (sin(ripplePhase) + 1.0f) * 0.35f;

    if (sceneMode == 2)
        glColor3f(0.25f, 0.45f, 0.65f);
    else
        glColor3f(0.62f, 0.90f, 1.0f);

    drawRipple(34.0f + boatX, 5.6f, 2.5f + p, 0.45f + p * 0.15f);

    if (sceneMode == 0 || sceneMode == 1)
        drawRipple(72.0f + duckOffset, 7.4f, 1.7f + p * 0.7f, 0.30f + p * 0.10f);
}

void drawTwinklingStars()
{
    if (sceneMode != 2)
        return;

    const float sx[12] = {8, 16, 24, 32, 41, 51, 59, 68, 76, 86, 92, 97};
    const float sy[12] = {70, 76, 66, 72, 78, 69, 74, 65, 76, 71, 64, 78};

    for (int i = 0; i < 12; i++)
    {
        float glow = 0.08f + (sin(starTwinklePhase + i * 0.8f) + 1.0f) * 0.07f;
        glColor3f(1.0f, 0.98f, 0.72f);
        circle(sx[i], sy[i], glow, 18);
    }
}

void drawRainSplashes()
{
    if (sceneMode != 3)
        return;

    glColor3f(0.75f, 0.85f, 1.0f);
    float wave = fabs(sin(rainSplashPhase)) * 0.45f;

    for (int i = 0; i < 10; i++)
    {
        float x = 5.0f + i * 9.5f;
        float y = 16.3f + (i % 2) * 0.25f;
        line(x, y, x - 0.8f - wave, y + 0.45f, 1.0f);
        line(x, y, x + 0.8f + wave, y + 0.45f, 1.0f);
    }
}

void drawCloud(float x, float y, float s)
{
    if (sceneMode == 3)
        glColor3f(0.34f, 0.35f, 0.38f);
    else
        glColor3f(1.0f, 1.0f, 1.0f);
    ellipse(x, y, 2.8f*s, 1.7f*s);
    ellipse(x+3.0f*s, y+0.9f*s, 3.6f*s, 2.5f*s);
    ellipse(x+6.8f*s, y+0.8f*s, 3.4f*s, 2.4f*s);
    ellipse(x+9.6f*s, y, 2.6f*s, 1.7f*s);
    rect(x, y-1.0f*s, x+9.6f*s, y+0.6f*s);
}
void drawClouds()
{
    if (sceneMode == 2)
        return;
    glPushMatrix();
    glTranslatef(cloudOffsetA, 0, 0);
    drawCloud(8, 67, 0.75f);
    drawCloud(42, 72, 0.55f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(cloudOffsetB, 0, 0);
    drawCloud(66, 65, 0.86f);
    drawCloud(91, 73, 0.60f);
    glPopMatrix();
}
void drawHills()
{
    if (sceneMode == 2)
        glColor3f(0.06f, 0.18f, 0.12f);
    else
        glColor3f(0.12f, 0.50f, 0.28f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0, 36);
    glVertex2f(18, 50);
    glVertex2f(36, 36);
    glVertex2f(24, 36);
    glVertex2f(50, 52);
    glVertex2f(70, 36);
    glVertex2f(55, 36);
    glVertex2f(78, 49);
    glVertex2f(100, 36);
    glEnd();
    if (sceneMode == 2)
        glColor3f(0.08f, 0.24f, 0.10f);
    else
        glColor3f(0.24f, 0.68f, 0.30f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 36);
    glVertex2f(15, 38);
    glVertex2f(32, 37);
    glVertex2f(50, 40);
    glVertex2f(68, 38);
    glVertex2f(84, 41);
    glVertex2f(100, 39);
    glVertex2f(100, 17);
    glVertex2f(0, 17);
    glEnd();
}
void drawBird(float x, float y, float s)
{
    float flap = sin(wingPhase) * 0.7f * s;
    glColor3f(0.02f, 0.02f, 0.02f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(x, y);
    glVertex2f(x+1.4f*s, y-0.5f*s+flap);
    glVertex2f(x+2.8f*s, y+0.1f*s);
    glEnd();
}
void drawBirds()
{
    if (sceneMode == 2 || sceneMode == 3)
        return;
    glPushMatrix();
    glTranslatef(birdOffset, 0, 0);
    drawBird(31, 62, 0.8f);
    drawBird(35, 64, 0.7f);
    drawBird(38, 61, 0.85f);
    drawBird(42, 63, 0.75f);
    glPopMatrix();
}

void drawPaddyField()
{
    if (sceneMode == 2)
        glColor3f(0.20f, 0.34f, 0.08f);
    else
        glColor3f(0.72f, 0.82f, 0.12f);

    glBegin(GL_POLYGON);
    glVertex2f(0, 17);
    glVertex2f(34, 17);
    glVertex2f(39, 28);
    glVertex2f(0, 30);
    glEnd();

    glColor3f(0.38f, 0.50f, 0.06f);
    for (float y = 19; y < 28; y += 2.0f)
        line(0, y, 36, y+0.8f, 1.0f);

    if (sceneMode == 2)
        glColor3f(0.08f, 0.30f, 0.05f);
    else
        glColor3f(0.10f, 0.52f, 0.08f);

    for (float x = 2; x < 35; x += 3.0f)
    {
        for (float y = 20; y < 27; y += 3.0f)
        {
            float sway = sin(fieldPhase + x*0.22f + y*0.16f) * 0.28f;
            line(x, y, x-0.4f+sway, y+1.0f, 1.0f);
            line(x, y, x+0.4f+sway, y+1.0f, 1.0f);
        }
    }
}

void drawVillagePath()
{
    glColor3f(0.74f, 0.50f, 0.28f);
    glBegin(GL_POLYGON);
    glVertex2f(36, 17);
    glVertex2f(49, 17);
    glVertex2f(53, 24);
    glVertex2f(50, 31);
    glVertex2f(59, 37);
    glVertex2f(70, 40);
    glVertex2f(73, 44);
    glVertex2f(61, 42);
    glVertex2f(48, 36);
    glVertex2f(42, 30);
    glEnd();
    glColor3f(0.86f, 0.66f, 0.38f);
    line(42, 18, 49, 30, 1.3f);
    line(49, 30, 60, 40, 1.3f);
}

void drawBanyanTree()
{
    glColor3f(0.38f, 0.22f, 0.08f);

    glBegin(GL_POLYGON);
    glVertex2f(3, 19);
    glVertex2f(9, 19);
    glVertex2f(11, 36);
    glVertex2f(9, 48);
    glVertex2f(6, 49);
    glVertex2f(5, 36);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(7, 41);
    glVertex2f(10, 43);
    glVertex2f(19, 52);
    glVertex2f(17, 54);

    glVertex2f(7, 44);
    glVertex2f(9, 46);
    glVertex2f(4, 56);
    glVertex2f(2, 55);
    glEnd();

    glColor3f(0.28f, 0.16f, 0.07f);
    line(15, 50, 15, 39, 1.4f);
    line(19, 49, 19, 38, 1.4f);
    line(2, 50, 2, 40, 1.4f);

    glPushMatrix();
    glTranslatef(10.0f, 53.0f, 0.0f);
    glRotatef(sin(palmPhase*0.55f) * 1.4f, 0, 0, 1);
    glTranslatef(-10.0f, -53.0f, 0.0f);

    if (sceneMode == 2)
        glColor3f(0.0f, 0.20f, 0.03f);
    else
        glColor3f(0.02f, 0.48f, 0.08f);

    circle(5, 58, 8);
    circle(12, 60, 9);
    circle(19, 57, 8);
    circle(1, 53, 7);
    circle(10, 52, 8);
    circle(20, 51, 7);

    glPopMatrix();
}

void drawPalmTree(float x, float y, float s)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(s, s, 1);

    glColor3f(0.46f, 0.27f, 0.09f);
    glLineWidth(5.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0, 0);
    glVertex2f(0.3f, 7);
    glVertex2f(-0.1f, 14);
    glVertex2f(0.5f, 21);
    glEnd();

    float sway = sin(palmPhase + x*0.10f) * 2.8f;
    glPushMatrix();
    glTranslatef(0.5f, 21.0f, 0);
    glRotatef(sway, 0, 0, 1);
    glTranslatef(-0.5f, -21.0f, 0);

    if (sceneMode == 2)
        glColor3f(0.00f, 0.25f, 0.04f);
    else if (sceneMode == 3)
        glColor3f(0.04f, 0.36f, 0.07f);
    else
        glColor3f(0.04f, 0.55f, 0.09f);

    glBegin(GL_POLYGON);
    glVertex2f(0.5f, 21);
    glVertex2f(-2, 25.5f);
    glVertex2f(-6.5f, 27);
    glVertex2f(-4.5f, 24.5f);
    glVertex2f(-1.5f, 22);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.5f, 21);
    glVertex2f(-3, 22.5f);
    glVertex2f(-7.5f, 22);
    glVertex2f(-4, 20.5f);
    glVertex2f(-1, 20.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.5f, 21);
    glVertex2f(-2.5f, 19.5f);
    glVertex2f(-6.5f, 16.5f);
    glVertex2f(-4.2f, 17);
    glVertex2f(-1, 19.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.5f, 21);
    glVertex2f(3, 25.5f);
    glVertex2f(7, 27);
    glVertex2f(5, 24.5f);
    glVertex2f(1.5f, 22);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.5f, 21);
    glVertex2f(4, 22.5f);
    glVertex2f(7.5f, 22);
    glVertex2f(4.5f, 20.5f);
    glVertex2f(1, 20.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.5f, 21);
    glVertex2f(3, 19.5f);
    glVertex2f(6.5f, 16.5f);
    glVertex2f(4.2f, 17);
    glVertex2f(1, 19.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.5f, 21);
    glVertex2f(-1.2f, 25);
    glVertex2f(-1.8f, 29);
    glVertex2f(0, 27);
    glVertex2f(1, 23);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.5f, 21);
    glVertex2f(1.5f, 25);
    glVertex2f(2.8f, 29);
    glVertex2f(3, 26);
    glVertex2f(1.2f, 22);
    glEnd();

    glColor3f(0.18f, 0.28f, 0.04f);
    circle(0.5f, 21, 1.0f);

    glPopMatrix();
    glPopMatrix();
}

void drawBananaPlant(float x, float y, float s)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(s, s, 1);

    glColor3f(0.36f, 0.55f, 0.12f);
    rect(-0.45f, 0, 0.45f, 11);

    glPushMatrix();
    glTranslatef(0, 10.0f, 0);
    glRotatef(sin(bananaPhase + x*0.16f) * 3.2f, 0, 0, 1);
    glTranslatef(0, -10.0f, 0);

    if (sceneMode == 2)
        glColor3f(0.05f, 0.30f, 0.08f);
    else
        glColor3f(0.10f, 0.60f, 0.12f);

    glBegin(GL_POLYGON);
    glVertex2f(0, 9.5f);
    glVertex2f(-5, 14);
    glVertex2f(-2, 15);
    glVertex2f(0, 11);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0, 10);
    glVertex2f(5, 15);
    glVertex2f(2, 16);
    glVertex2f(0, 11);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0, 8.5f);
    glVertex2f(-4.5f, 8);
    glVertex2f(-2, 11);
    glVertex2f(0, 10);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0, 9);
    glVertex2f(4.5f, 9);
    glVertex2f(2, 12);
    glVertex2f(0, 10.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0, 10);
    glVertex2f(-2.5f, 16);
    glVertex2f(-0.5f, 17);
    glVertex2f(0.5f, 11);
    glEnd();

    glColor3f(0.70f, 0.75f, 0.05f);
    ellipse(0.8f, 8.8f, 0.7f, 1.6f);

    glPopMatrix();
    glPopMatrix();
}

void drawHouseOne()
{

    glColor3f(0.96f, 0.52f, 0.18f);
    glBegin(GL_QUADS);
    glVertex2f(24, 32);
    glVertex2f(38, 32);
    glVertex2f(38, 44);
    glVertex2f(24, 44);
    glEnd();

    glColor3f(0.84f, 0.34f, 0.10f);
    glBegin(GL_QUADS);
    glVertex2f(38, 32);
    glVertex2f(45, 35);
    glVertex2f(45, 45);
    glVertex2f(38, 44);
    glEnd();

    glColor3f(0.32f, 0.16f, 0.06f);
    glBegin(GL_POLYGON);
    glVertex2f(22, 44);
    glVertex2f(29, 51);
    glVertex2f(40, 51);
    glVertex2f(47, 45);
    glVertex2f(38, 43);
    glEnd();

    glColor3f(0.58f, 0.32f, 0.10f);
    for (float x = 24; x <= 38; x += 3.0f)
        line(x, 45, x + 5, 50, 1.0f);

    glColor3f(0.30f, 0.13f, 0.03f);
    glBegin(GL_QUADS);
    glVertex2f(33, 32);
    glVertex2f(36, 32);
    glVertex2f(36, 41);
    glVertex2f(33, 41);
    glEnd();

    glColor3f(0.64f, 0.43f, 0.23f);
    glBegin(GL_QUADS);
    glVertex2f(31, 30.5f);
    glVertex2f(38, 30.5f);
    glVertex2f(38, 32);
    glVertex2f(31, 32);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(32, 29.5f);
    glVertex2f(37, 29.5f);
    glVertex2f(37, 30.5f);
    glVertex2f(32, 30.5f);
    glEnd();

    if (sceneMode == 2 && houseLights)
        glColor3f(1.0f, 0.88f, 0.18f);
    else
        glColor3f(0.38f, 0.78f, 0.92f);

    glBegin(GL_QUADS);
    glVertex2f(26, 36);
    glVertex2f(30, 36);
    glVertex2f(30, 40);
    glVertex2f(26, 40);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(39, 37);
    glVertex2f(42, 37);
    glVertex2f(42, 40);
    glVertex2f(39, 40);
    glEnd();

    glColor3f(0.16f, 0.16f, 0.16f);
    line(28, 36, 28, 40, 1.0f);
    line(26, 38, 30, 38, 1.0f);
}

void drawHouseTwo()
{
    glColor3f(0.20f, 0.62f, 0.74f);
    glBegin(GL_POLYGON);
    glVertex2f(73, 27);
    glVertex2f(88, 27);
    glVertex2f(88, 39);
    glVertex2f(81, 45);
    glVertex2f(73, 39);
    glEnd();
    glColor3f(0.12f, 0.48f, 0.66f);
    glBegin(GL_QUADS);
    glVertex2f(88, 27);
    glVertex2f(96, 30);
    glVertex2f(96, 40);
    glVertex2f(88, 39);
    glEnd();
    glColor3f(0.82f, 0.24f, 0.10f);
    glBegin(GL_POLYGON);
    glVertex2f(71, 39);
    glVertex2f(80.5f, 46);
    glVertex2f(90, 46);
    glVertex2f(98, 40);
    glVertex2f(88, 38);
    glEnd();
    glColor3f(0.30f, 0.12f, 0.03f);
    rect(83, 27, 87, 36);
    if (sceneMode == 2 && houseLights)
        glColor3f(1.0f, 0.90f, 0.22f);
    else
        glColor3f(0.85f, 0.95f, 1.0f);
    rect(75.5f, 31, 79.5f, 35);
    rect(90, 32, 93, 35);
    glColor3f(0.18f, 0.18f, 0.18f);
    line(77.5f, 31, 77.5f, 35, 1.0f);
    line(75.5f, 33, 79.5f, 33, 1.0f);
}
void drawSmoke()
{
    if (sceneMode == 3)
        return;
    float rise = fmod(smokePhase, 6.0f);
    glColor3f(0.65f, 0.65f, 0.65f);
    ellipse(90, 46+rise, 1.1f, 0.7f);
    ellipse(91, 49+rise, 0.9f, 0.6f);
    ellipse(89.5f, 52+rise, 0.7f, 0.5f);
}
void drawChimney()
{
    glColor3f(0.30f, 0.12f, 0.05f);
    rect(88.5f, 43, 91, 48);
    drawSmoke();
}

void drawCow(float x, float y, float s)
{
    glPushMatrix();
    glTranslatef(x, y + sin(cowLegPhase)*0.10f, 0);
    glScalef(s, s, 1);

    if (sceneMode == 2)
        glColor3f(0.65f, 0.65f, 0.62f);
    else
        glColor3f(0.95f, 0.95f, 0.90f);
    ellipse(0, 3, 4.5f, 2.5f);

    glColor3f(0.08f, 0.08f, 0.08f);
    ellipse(-1.5f, 3.8f, 1.2f, 0.8f);
    ellipse(1.5f, 2.4f, 1.0f, 0.7f);
    ellipse(0.5f, 4.2f, 0.7f, 0.5f);

    glPushMatrix();
    glTranslatef(4.5f, 3.5f, 0);
    glRotatef(sin(cowLegPhase*0.65f)*2.0f, 0, 0, 1);
    glTranslatef(-4.5f, -3.5f, 0);

    glColor3f(0.90f, 0.85f, 0.75f);
    ellipse(4.5f, 3.5f, 1.7f, 1.5f);

    glColor3f(0.85f, 0.55f, 0.55f);
    ellipse(5.3f, 3.0f, 1.0f, 0.6f);

    glColor3f(0, 0, 0);
    circle(4.8f, 4.0f, 0.15f);

    glColor3f(0.75f, 0.55f, 0.40f);
    glBegin(GL_TRIANGLES);
    glVertex2f(3.7f, 4.5f);
    glVertex2f(2.7f, 5.2f);
    glVertex2f(3.9f, 4.9f);
    glVertex2f(5.1f, 4.6f);
    glVertex2f(6.0f, 5.2f);
    glVertex2f(5.0f, 4.9f);
    glEnd();

    glColor3f(0.90f, 0.80f, 0.55f);
    glBegin(GL_TRIANGLES);
    glVertex2f(4.0f, 4.8f);
    glVertex2f(4.1f, 6.0f);
    glVertex2f(4.5f, 4.8f);
    glVertex2f(4.9f, 4.8f);
    glVertex2f(5.2f, 6.0f);
    glVertex2f(5.4f, 4.7f);
    glEnd();

    glPopMatrix();

    float leg = sin(cowLegPhase) * 0.28f;
    glColor3f(0.85f, 0.82f, 0.75f);
    rect(-3.0f + leg, -0.5f, -2.3f + leg, 2);
    rect(-1.5f - leg, -0.5f, -0.8f - leg, 2);
    rect(1.5f - leg, -0.5f, 2.2f - leg, 2);
    rect(2.8f + leg, -0.5f, 3.5f + leg, 2);

    glColor3f(0.10f, 0.08f, 0.06f);
    rect(-3.1f + leg, -0.8f, -2.2f + leg, -0.3f);
    rect(-1.6f - leg, -0.8f, -0.7f - leg, -0.3f);
    rect(1.4f - leg, -0.8f, 2.3f - leg, -0.3f);
    rect(2.7f + leg, -0.8f, 3.6f + leg, -0.3f);

    float tailSwing = sin(cowTailPhase) * 1.1f;
    glColor3f(0.30f, 0.20f, 0.10f);
    line(-4.2f, 4.0f, -5.5f, 1.5f + tailSwing, 1.5f);
    glColor3f(0.05f, 0.05f, 0.05f);
    circle(-5.5f, 1.3f + tailSwing, 0.35f);

    glPopMatrix();
}

void drawFence(float x1, float x2, float y)
{
    glColor3f(0.50f, 0.31f, 0.10f);
    rect(x1, y+1.5f, x2, y+1.9f);
    rect(x1, y+3.2f, x2, y+3.6f);
    for (float x = x1; x <= x2; x += 1.6f)
    {
        rect(x, y, x+0.28f, y+5.2f);
        glBegin(GL_TRIANGLES);
        glVertex2f(x, y+5.2f);
        glVertex2f(x+0.28f, y+5.2f);
        glVertex2f(x+0.14f, y+5.8f);
        glEnd();
    }
}

void drawChicken(float x, float y, float s)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(s, s, 1);

    glColor3f(0.95f, 0.92f, 0.80f);
    ellipse(0, 0, 1.5f, 1.0f);

    circle(1.3f, 0.8f, 0.55f);

    glColor3f(0.95f, 0.10f, 0.08f);
    circle(1.25f, 1.35f, 0.22f);

    glColor3f(1.0f, 0.65f, 0.05f);
    glBegin(GL_TRIANGLES);
    glVertex2f(1.8f, 0.8f);
    glVertex2f(2.3f, 0.65f);
    glVertex2f(1.8f, 0.45f);
    glEnd();

    glColor3f(0, 0, 0);
    circle(1.45f, 0.95f, 0.08f);

    glColor3f(0.85f, 0.55f, 0.10f);
    line(-0.5f, -1.0f, -0.5f, -1.5f, 1.0f);
    line(0.5f, -1.0f, 0.5f, -1.5f, 1.0f);

    glPopMatrix();
}

void drawFlower(float x, float y, float s)
{
    float sway = sin(flowerPhase + x*0.25f) * 0.22f * s;
    float hx = x + sway;

    glColor3f(0.10f, 0.45f, 0.12f);
    line(x, y, hx, y+1.8f*s, 1.0f);

    glColor3f(1.0f, 0.24f, 0.50f);
    circle(hx-0.35f*s, y+2.0f*s, 0.35f*s);
    circle(hx+0.35f*s, y+2.0f*s, 0.35f*s);
    circle(hx, y+2.35f*s, 0.35f*s);
    circle(hx, y+1.7f*s, 0.35f*s);

    glColor3f(1.0f, 0.78f, 0.06f);
    circle(hx, y+2.0f*s, 0.25f*s);
}

void drawFlowerGarden()
{
    for (int i = 0; i < 9; i++)
    {
        drawFlower(
            52.0f + i*1.2f,
            20.0f + (i%2)*0.5f,
            0.7f
        );
    }
}
void drawClothesline()
{
    glColor3f(0.35f, 0.20f, 0.08f);
    rect(59, 25, 59.4f, 34);
    rect(69, 25, 69.4f, 34);
    glColor3f(0.10f, 0.10f, 0.10f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 30; i++)
    {
        float t = i / 30.0f;
        float x =
            59.4f +
            (69.0f - 59.4f) * t;
        float y =
            33.3f -
            sin(t * PI) * 0.5f;
        glVertex2f(x, y);
    }
    glEnd();
    if (sceneMode == 2 || sceneMode == 3)
        return;
    float wave = sin(clothPhase) * 0.35f;
    glColor3f(0.95f, 0.12f, 0.18f);
    glBegin(GL_POLYGON);
    glVertex2f(60.0f, 33.0f);
    glVertex2f(62.0f, 32.9f);
    glVertex2f(62.0f+wave, 28.5f);
    glVertex2f(60.0f+wave, 28.7f);
    glEnd();
    glColor3f(1.0f, 0.72f, 0.05f);
    glBegin(GL_POLYGON);
    glVertex2f(63.0f, 32.8f);
    glVertex2f(65.5f, 32.7f);
    glVertex2f(65.7f-wave, 29.0f);
    glVertex2f(64.8f-wave, 28.7f);
    glVertex2f(64.2f, 30.5f);
    glVertex2f(63.4f-wave, 28.8f);
    glVertex2f(62.7f-wave, 29.0f);
    glEnd();
    glColor3f(0.08f, 0.45f, 0.92f);
    glBegin(GL_POLYGON);
    glVertex2f(66.3f, 32.7f);
    glVertex2f(68.3f, 32.6f);
    glVertex2f(68.2f+wave, 28.8f);
    glVertex2f(66.5f+wave, 29.0f);
    glEnd();
}
void drawRiver()
{
    glBegin(GL_QUAD_STRIP);
    for (float x = 0; x <= 100; x += 1.0f)
    {
        float top =
            16.0f +
            sin(x*0.20f + riverPhase) * 0.65f;
        if (sceneMode == 2)
            glColor3f(0.02f, 0.22f, 0.45f);
        else
            glColor3f(0.00f, 0.56f, 0.92f);
        glVertex2f(x, top);
        if (sceneMode == 2)
            glColor3f(0.01f, 0.10f, 0.28f);
        else
            glColor3f(0.00f, 0.32f, 0.68f);
        glVertex2f(x, 0);
    }
    glEnd();
    if (sceneMode != 2)
    {
        glColor3f(0.48f, 0.88f, 1.0f);
        for (int i = 0; i < 9; i++)
        {
            float y = 2.0f + i*1.3f;
            line(
                5+i*9,
                y,
                11+i*9,
                y+0.2f,
                1.0f
            );
        }
    }
}
void drawReflection()
{
    if (sceneMode == 3)
        return;
    float shimmer =
        sin(reflectionPhase) *
        0.8f;
    if (sceneMode == 0)
        glColor3f(1.0f, 0.70f, 0.18f);
    else if (sceneMode == 1)
        glColor3f(1.0f, 0.35f, 0.10f);
    else
        glColor3f(0.70f, 0.75f, 0.90f);
    for (int i = 0; i < 6; i++)
    {
        float w = 6.0f - i*0.6f;
        line(
            75-w/2 + shimmer*0.2f,
            11-i*1.3f,
            75+w/2 + shimmer*0.2f,
            11-i*1.3f,
            1.2f
        );
    }
}
void drawBridge()
{
    glColor3f(0.46f, 0.25f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(48, 13);
    glVertex2f(67, 13);
    glVertex2f(70, 17);
    glVertex2f(51, 17);
    glEnd();
    glColor3f(0.72f, 0.46f, 0.18f);
    for (float x = 50; x < 69; x += 2.0f)
    {
        line(
            x,
            13.2f,
            x+2.5f,
            16.8f,
            1.3f
        );
    }
    glColor3f(0.32f, 0.18f, 0.06f);
    rect(50, 13, 50.5f, 20);
    rect(68.5f, 13, 69, 20);
    line(50.2f, 19, 68.7f, 19, 2.0f);
}
void drawBoatBody()
{
    glColor3f(0.32f, 0.15f, 0.04f);
    glBegin(GL_POLYGON);
    glVertex2f(24, 6);
    glVertex2f(40, 6);
    glVertex2f(45, 10);
    glVertex2f(39, 9);
    glVertex2f(28, 9);
    glVertex2f(22, 11);
    glEnd();
    glColor3f(0.20f, 0.07f, 0.02f);
    glBegin(GL_POLYGON);
    glVertex2f(25, 9.3f);
    glVertex2f(42, 9.5f);
    glVertex2f(39, 8.7f);
    glVertex2f(28, 8.7f);
    glEnd();
}
void drawFisherman()
{
    float rowAngle = sin(oarPhase) * 18.0f;

    glColor3f(0.80f, 0.52f, 0.30f);
    circle(36, 13.8f, 0.75f);
    glColor3f(0.04f, 0.03f, 0.02f);
    ellipse(36, 14.2f, 0.85f, 0.35f);

    glColor3f(1.0f, 0.66f, 0.04f);
    glBegin(GL_POLYGON);
    glVertex2f(35.2f, 10.5f);
    glVertex2f(36.8f, 10.5f);
    glVertex2f(36.7f, 13.2f);
    glVertex2f(35.4f, 13.2f);
    glEnd();

    glColor3f(0.72f, 0.10f, 0.04f);
    rect(35.2f, 8.8f, 36.8f, 10.5f);

    glColor3f(0.80f, 0.52f, 0.30f);
    line(35.5f, 12.3f, 36.7f, 11.8f, 2.0f);

    glPushMatrix();
    glTranslatef(36.7f, 11.8f, 0.0f);
    glRotatef(rowAngle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.80f, 0.52f, 0.30f);
    line(0.0f, 0.0f, 1.7f, -0.4f, 2.0f);

    glColor3f(0.23f, 0.11f, 0.04f);
    line(-2.2f, 4.2f, 8.8f, -6.1f, 3.0f);

    glBegin(GL_POLYGON);
    glVertex2f(7.8f, -5.3f);
    glVertex2f(9.3f, -6.7f);
    glVertex2f(10.8f, -6.1f);
    glVertex2f(9.3f, -4.8f);
    glEnd();

    glPopMatrix();
}
void drawBoat()
{
    glPushMatrix();
    glTranslatef(boatX, 0, 0);
    if (boatDirection < 0)
    {
        glTranslatef(34, 0, 0);
        glScalef(-1, 1, 1);
        glTranslatef(-34, 0, 0);
    }
    drawBoatBody();
    if (sceneMode != 3)
        drawFisherman();
    glPopMatrix();
}
void drawDuck(float x, float y, float s)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(s, s, 1);
    glColor3f(0.95f, 0.92f, 0.75f);
    ellipse(0, 0, 1.8f, 0.8f);
    circle(1.4f, 0.8f, 0.6f);
    glColor3f(1.0f, 0.55f, 0.05f);
    glBegin(GL_TRIANGLES);
    glVertex2f(1.9f, 0.9f);
    glVertex2f(2.8f, 0.7f);
    glVertex2f(1.9f, 0.5f);
    glEnd();
    glColor3f(0, 0, 0);
    circle(1.55f, 1.0f, 0.12f);
    glPopMatrix();
}
void drawDucks()
{
    if (sceneMode == 2 || sceneMode == 3)
        return;
    glPushMatrix();
    glTranslatef(duckOffset, 0, 0);
    drawDuck(72, 8, 0.8f);
    drawDuck(77, 6.5f, 0.65f);
    glPopMatrix();
}

void drawOneFish(float x, float y, float s, bool faceRight, float phase)
{
    glPushMatrix();
    glTranslatef(x, y + sin(phase)*0.30f, 0);
    glScalef(faceRight ? s : -s, s, 1);

    if (sceneMode == 2)
        glColor3f(0.75f, 0.30f, 0.06f);
    else
        glColor3f(1.0f, 0.45f, 0.05f);

    ellipse(0, 0, 1.5f, 0.65f);

    float tail = sin(phase*2.2f) * 0.35f;
    glBegin(GL_TRIANGLES);
    glVertex2f(-1.3f, 0);
    glVertex2f(-2.5f, 1.0f + tail);
    glVertex2f(-2.5f, -1.0f + tail);
    glEnd();

    glColor3f(1.0f, 0.75f, 0.15f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0, 0.4f);
    glVertex2f(-0.5f, 1.2f);
    glVertex2f(0.7f, 0.5f);
    glEnd();

    glColor3f(1, 1, 1);
    circle(0.8f, 0.2f, 0.22f);
    glColor3f(0, 0, 0);
    circle(0.85f, 0.22f, 0.10f);

    glPopMatrix();
}

void drawFish()
{
    if (sceneMode == 3)
    {
        float jump1 = fabs(sin(fishPhase)) * 5.0f;
        float jump2 = fabs(sin(fishPhase + 1.0f)) * 4.0f;
        float jump3 = fabs(sin(fishPhase + 2.0f)) * 5.5f;
        float jump4 = fabs(sin(fishPhase + 3.0f)) * 4.5f;
        float jump5 = fabs(sin(fishPhase + 4.0f)) * 5.0f;

        drawOneFish(12.0f, 11.0f + jump1, 0.8f, true, fishPhase);
        drawOneFish(26.0f, 11.0f + jump2, 0.6f, false, fishPhase + 1.0f);
        drawOneFish(43.0f, 11.0f + jump3, 0.7f, true, fishPhase + 2.0f);
        drawOneFish(79.0f, 11.0f + jump4, 0.9f, false, fishPhase + 3.0f);
        drawOneFish(92.0f, 11.0f + jump5, 0.6f, true, fishPhase + 4.0f);
        return;
    }

    float a = fmod(fishSwim * 0.85f, 112.0f) - 8.0f;
    float b = fmod(fishSwim * 0.62f + 30.0f, 116.0f) - 10.0f;
    float c = fmod(fishSwim * 1.05f + 58.0f, 120.0f) - 12.0f;
    float d = fmod(fishSwim * 0.72f + 86.0f, 118.0f) - 10.0f;
    float e = fmod(fishSwim * 0.55f + 14.0f, 114.0f) - 8.0f;

    drawOneFish(a, 7.0f, 0.8f, true, fishPhase);
    drawOneFish(100.0f-b, 4.0f, 0.6f, false, fishPhase + 1.4f);
    drawOneFish(c, 7.0f, 0.7f, true, fishPhase + 2.1f);
    drawOneFish(100.0f-d, 5.0f, 0.9f, false, fishPhase + 3.0f);
    drawOneFish(e, 10.0f, 0.6f, true, fishPhase + 4.0f);
}

void drawFireflies()
{
    if (sceneMode != 2)
        return;
    glPointSize(5.0f);
    glColor3f(1.0f, 0.95f, 0.15f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 15; i++)
    {
        float x =
            5.0f +
            i * 6.2f;
        float y =
            20.0f +
            sin(fireflyPhase + i) * 4.0f;
        glVertex2f(x, y);
    }
    glEnd();
}
void drawRain()
{
    if (sceneMode != 3)
        return;
    glColor3f(0.82f, 0.88f, 1.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 260; i++)
    {
        glVertex2f(rainX[i], rainY[i]);
        glVertex2f(rainX[i]-0.6f, rainY[i]-1.7f);
    }
    glEnd();
    if (lightningTimer > 0)
    {
        glColor3f(1.0f, 1.0f, 0.85f);
        glLineWidth(3.0f);
        glBegin(GL_LINE_STRIP);
        glVertex2f(78, 78);
        glVertex2f(74, 66);
        glVertex2f(79, 66);
        glVertex2f(73, 54);
        glEnd();
    }
}
void drawHelpPanel()
{
    if (!showHelp)
        return;
    glColor3f(0.03f, 0.03f, 0.05f);
    rect(65.0f, 71.0f, 99.0f, 79.0f);
    glColor3f(1.0f, 0.82f, 0.22f);
    drawText(
        66,
        76.8f,
        "DREAMLAND VILLAGE ULTIMATE",
        GLUT_BITMAP_HELVETICA_18
    );
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(
        66,
        74.2f,
        "1 Day | 2 Sunset | 3 Night | 4 Rain | M/U Sound",
        GLUT_BITMAP_HELVETICA_12
    );
    drawText(
        66,
        72.3f,
        "B Boat | L Light | H Help | F Fullscreen | Arrow Boat",
        GLUT_BITMAP_HELVETICA_12
    );
}

void display()
{
    if (introScreen)
    {
        drawIntro();
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    drawSky();
    drawSunMoonStars();
    drawSunRays();
    drawTwinklingStars();
    drawClouds();
    drawBirds();
    drawHills();
    drawPaddyField();

    if (sceneMode == 0 || sceneMode == 1)
        drawChicken(chickenX, 22.0f + sin(chickenWalkPhase) * 0.05f, 0.65f);

    drawGrassDetails();

    if (sceneMode == 0 || sceneMode == 1)
    {
        glPushMatrix();

        if (cowDirection < 0)
        {
            glTranslatef(cowX, 0, 0);
            glScalef(-1, 1, 1);
            glTranslatef(-cowX, 0, 0);
        }

        drawCow(cowX, 27.5f, 0.85f);
        glPopMatrix();
    }

    drawVillagePath();

    drawPalmTree(50, 37, 0.65f);
    drawPalmTree(57, 40, 0.70f);
    drawPalmTree(68, 37, 0.60f);
    drawPalmTree(96, 39, 0.70f);

    drawHouseOne();
    drawHouseTwo();
    drawChimney();

    drawFence(0, 22, 20);
    drawFence(72, 100, 21);
    drawBanyanTree();

    drawBananaPlant(20, 33, 0.95f);
    drawBananaPlant(54, 27, 0.85f);

    drawFlowerGarden();
    drawClothesline();

    drawRiver();
    drawRiverRipples();
    drawReflection();
    drawFish();
    drawBridge();
    drawBoat();
    drawDucks();

    drawFireflies();
    drawRain();
    drawRainSplashes();
    drawHelpPanel();

    glutSwapBuffers();
}

void update(int)
{
    cloudOffsetA += 0.012f;
    cloudOffsetB += 0.020f;

    if (cloudOffsetA > 110)
        cloudOffsetA = -110;
    if (cloudOffsetB > 110)
        cloudOffsetB = -110;

    birdOffset += 0.025f;
    if (birdOffset > 85)
        birdOffset = -55;

    wingPhase += 0.18f;
    riverPhase += 0.06f;
    reflectionPhase += 0.05f;

    palmPhase += 0.035f;
    bananaPhase += 0.040f;
    flowerPhase += 0.055f;
    fieldPhase += 0.050f;

    sunRayPhase += 0.18f;
    grassPhase += 0.055f;
    ripplePhase += 0.065f;
    starTwinklePhase += 0.075f;
    rainSplashPhase += 0.18f;

    if (sceneMode == 0 || sceneMode == 1)
    {
        cowX += 0.012f * cowDirection;

        if (cowX + 5.0f >= 28.0f)
        {
            cowX -= 0.012f;
            cowDirection = -1;
        }
        else if (cowX - 5.0f <= 5.0f)
        {
            cowX += 0.012f;
            cowDirection = 1;
        }

        cowLegPhase += 0.12f;
        cowTailPhase += 0.16f;

        chickenWalkPhase += 0.08f;

        chickenX += 0.004f;
        if (chickenX > 33.0f)
            chickenX = 22.0f;
    }

    if (boatMoving && sceneMode != 3)
    {
        boatX += 0.06f * boatDirection;
        if (boatX > 58)
            boatX = -25;
        if (boatX < -25)
            boatX = 58;
    }

    duckOffset += 0.025f;
    if (duckOffset > 30)
        duckOffset = -45;

    fishPhase += 0.07f;
    fishSwim += 0.08f;

    if (boatMoving && sceneMode != 3)
        oarPhase += 0.08f;

    smokePhase += 0.03f;
    clothPhase += 0.08f;
    fireflyPhase += 0.07f;

    if (sceneMode == 3)
    {
        for (int i = 0; i < 260; i++)
        {
            rainY[i] -= 0.90f;
            rainX[i] -= 0.22f;

            if (rainY[i] < 0)
            {
                rainY[i] = 80;
                rainX[i] = (float)(rand() % 110);
            }
        }

        if (rand() % 180 == 0)
            lightningTimer = 8;

        if (lightningTimer > 0)
            lightningTimer--;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void toggleFullScreen()
{
    if (!fullScreen)
    {
        glutFullScreen();
        fullScreen = true;
    }
    else
    {
        glutReshapeWindow(1280, 720);
        glutPositionWindow(70, 40);
        fullScreen = false;
    }
}

void keyboard(unsigned char key, int, int)
{
    if (introScreen)
    {
        if (key == 'f' || key == 'F')
            toggleFullScreen();

        if (key == 13)
        {
            introScreen = false;
            updateSound();
            glutTimerFunc(10000, cowSoundTimer, 0);
        }
        glutPostRedisplay();
        return;
    }
    switch (key)
    {
        case '1':
            sceneMode = 0;
            updateSound();
            break;
        case '2':
            sceneMode = 1;
            updateSound();
            break;
        case '3':
            sceneMode = 2;
            updateSound();
            break;
        case '4':
            sceneMode = 3;
            updateSound();
            break;
        case 'd':
        case 'D':
            sceneMode = 0;
            updateSound();
            break;
        case 'n':
        case 'N':
            sceneMode = 2;
            updateSound();
            break;
        case 'r':
        case 'R':
            sceneMode = 3;
            updateSound();
            break;
        case 'b':
        case 'B':
            boatMoving = !boatMoving;
            break;
        case 'l':
        case 'L':
            houseLights = !houseLights;
            break;
        case 'h':
        case 'H':
            showHelp = !showHelp;
            break;
        case 'f':
        case 'F':
            toggleFullScreen();
            break;
        case 'm':
        case 'M':
            musicOn = false;
            stopSound();
            break;
        case 'u':
        case 'U':
            musicOn = true;
            updateSound();
            break;
        case 27:
            stopSound();
            exit(0);
            break;
    }
    glutPostRedisplay();
}
void specialKeys(int key, int, int)
{
    if (key == GLUT_KEY_LEFT)
    {
        boatDirection = -1;
        boatMoving = true;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        boatDirection = 1;
        boatMoving = true;
    }
    glutPostRedisplay();
}
void mouse(int button, int state, int, int)
{
    if (state != GLUT_DOWN)
        return;
    if (button == GLUT_LEFT_BUTTON)
    {
        boatDirection = 1;
        boatMoving = true;
    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
        boatDirection = -1;
        boatMoving = true;
    }
    else if (button == GLUT_MIDDLE_BUTTON)
    {
        boatMoving = false;
    }
}
void init()
{
    glClearColor(0.65f, 0.85f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 100.0, 0.0, 80.0);
    for (int i = 0; i < 260; i++)
    {
        rainX[i] = (float)(rand() % 100);
        rainY[i] = (float)(rand() % 80);
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGB
    );
    glutInitWindowSize(
        1280,
        720
    );
    glutInitWindowPosition(
        70,
        40
    );
    glutCreateWindow(
        "DREAMLAND VILLAGE ULTIMATE"
    );
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
