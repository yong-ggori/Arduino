//#include <MsTimer2.h>

// TETRIS
#include <FastLED.h>
#include <LEDMatrix.h>
#include <LEDSprites.h>
#include <LEDText.h>
#include <FontMatrise.h>
#include <HardwareSerial.h>
//#include "BluetoothSerial.h"
HardwareSerial mySerial(2);

#define LED_PIN        13 //13번 핀 사용
#define COLOR_ORDER    GRB //컬러
#define CHIPSET        WS2812B //3색 LED
#define MATRIX_WIDTH   8
#define MATRIX_HEIGHT  32
#define MATRIX_TYPE    HORIZONTAL_ZIGZAG_MATRIX

// NOTE the '-' sign before the width, this is due to my leds matrix origin being on the right hand side
cLEDMatrix < -MATRIX_WIDTH, -MATRIX_HEIGHT, MATRIX_TYPE > leds;

//BluetoothSerial SerialBT;

#define TARGET_FRAME_TIME    15  // Desired update rate, though if too many leds it will just run as fast as it can!
int INITIAL_DROP_FRAMES = 40;  // Start of game block drop delay in frames

// Bluetooth input
enum btnInput {NONE, ROTATE, DOWN, LEFT, RIGHT};
btnInput currentInput = NONE;

const uint8_t TetrisIData[] =
{
  // Frame 1
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(11110000),
  // Frame 2
  B8_3BIT(10000000),
  B8_3BIT(10000000),
  B8_3BIT(10000000),
  B8_3BIT(10000000),
  // Frame 3
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(11110000),
  // Frame 4
  B8_3BIT(10000000),
  B8_3BIT(10000000),
  B8_3BIT(10000000),
  B8_3BIT(10000000)
};
const uint8_t TetrisIMask[] =
{
  // Frame 1
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11110000),
  // Frame 2
  B8_1BIT(10000000),
  B8_1BIT(10000000),
  B8_1BIT(10000000),
  B8_1BIT(10000000),
  // Frame 3
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11110000),
  // Frame 4
  B8_1BIT(10000000),
  B8_1BIT(10000000),
  B8_1BIT(10000000),
  B8_1BIT(10000000)
};
const uint8_t TetrisJData[] =
{
  // Frame 1
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(22200000),
  B8_3BIT(00200000),
  // Frame 2
  B8_3BIT(00000000),
  B8_3BIT(02000000),
  B8_3BIT(02000000),
  B8_3BIT(22000000),
  // Frame 3
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(20000000),
  B8_3BIT(22200000),
  // Frame 4
  B8_3BIT(00000000),
  B8_3BIT(22000000),
  B8_3BIT(20000000),
  B8_3BIT(20000000)
};
const uint8_t TetrisJMask[] =
{
  // Frame 1
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11100000),
  B8_1BIT(00100000),
  // Frame 2
  B8_1BIT(00000000),
  B8_1BIT(01000000),
  B8_1BIT(01000000),
  B8_1BIT(11000000),
  // Frame 3
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(10000000),
  B8_1BIT(11100000),
  // Frame 4
  B8_1BIT(00000000),
  B8_1BIT(11000000),
  B8_1BIT(10000000),
  B8_1BIT(10000000)
};
const uint8_t TetrisLData[] =
{
  // Frame 1
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(33300000),
  B8_3BIT(30000000),
  // Frame 2
  B8_3BIT(00000000),
  B8_3BIT(33000000),
  B8_3BIT(03000000),
  B8_3BIT(03000000),
  // Frame 3
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(00300000),
  B8_3BIT(33300000),
  // Frame 4
  B8_3BIT(00000000),
  B8_3BIT(30000000),
  B8_3BIT(30000000),
  B8_3BIT(33000000)
};
const uint8_t TetrisLMask[] =
{
  // Frame 1
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11100000),
  B8_1BIT(10000000),
  // Frame 2
  B8_1BIT(00000000),
  B8_1BIT(11000000),
  B8_1BIT(01000000),
  B8_1BIT(01000000),
  // Frame 3
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(00100000),
  B8_1BIT(11100000),
  // Frame 4
  B8_1BIT(00000000),
  B8_1BIT(10000000),
  B8_1BIT(10000000),
  B8_1BIT(11000000)
};
const uint8_t TetrisOData[] =
{
  // Frame 1
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(44000000),
  B8_3BIT(44000000),
  // Frame 2
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(44000000),
  B8_3BIT(44000000),
  // Frame 3
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(44000000),
  B8_3BIT(44000000),
  // Frame 4
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(44000000),
  B8_3BIT(44000000)
};
const uint8_t TetrisOMask[] =
{
  // Frame 1
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11000000),
  B8_1BIT(11000000),
  // Frame 2
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11000000),
  B8_1BIT(11000000),
  // Frame 3
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11000000),
  B8_1BIT(11000000),
  // Frame 4
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11000000),
  B8_1BIT(11000000)
};
const uint8_t TetrisSData[] =
{
  // Frame 1
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(05500000),
  B8_3BIT(55000000),
  // Frame 2
  B8_3BIT(00000000),
  B8_3BIT(50000000),
  B8_3BIT(55000000),
  B8_3BIT(05000000),
  // Frame 3
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(05500000),
  B8_3BIT(55000000),
  // Frame 4
  B8_3BIT(00000000),
  B8_3BIT(50000000),
  B8_3BIT(55000000),
  B8_3BIT(05000000)
};
const uint8_t TetrisSMask[] =
{
  // Frame 1
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(01100000),
  B8_1BIT(11000000),
  // Frame 2
  B8_1BIT(00000000),
  B8_1BIT(10000000),
  B8_1BIT(11000000),
  B8_1BIT(01000000),
  // Frame 3
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(01100000),
  B8_1BIT(11000000),
  // Frame 4
  B8_1BIT(00000000),
  B8_1BIT(10000000),
  B8_1BIT(11000000),
  B8_1BIT(01000000)
};
const uint8_t TetrisTData[] =
{
  // Frame 1
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(66600000),
  B8_3BIT(06000000),
  // Frame 2
  B8_3BIT(00000000),
  B8_3BIT(06000000),
  B8_3BIT(66000000),
  B8_3BIT(06000000),
  // Frame 3
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(06000000),
  B8_3BIT(66600000),
  // Frame 4
  B8_3BIT(00000000),
  B8_3BIT(60000000),
  B8_3BIT(66000000),
  B8_3BIT(60000000)
};
const uint8_t TetrisTMask[] =
{
  // Frame 1
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11100000),
  B8_1BIT(01000000),
  // Frame 2
  B8_1BIT(00000000),
  B8_1BIT(01000000),
  B8_1BIT(11000000),
  B8_1BIT(01000000),
  // Frame 3
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(01000000),
  B8_1BIT(11100000),
  // Frame 4
  B8_1BIT(00000000),
  B8_1BIT(10000000),
  B8_1BIT(11000000),
  B8_1BIT(10000000)
};
const uint8_t TetrisZData[] =
{
  // Frame 1
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(77000000),
  B8_3BIT(07700000),
  // Frame 2
  B8_3BIT(00000000),
  B8_3BIT(07000000),
  B8_3BIT(77000000),
  B8_3BIT(70000000),
  // Frame 3
  B8_3BIT(00000000),
  B8_3BIT(00000000),
  B8_3BIT(77000000),
  B8_3BIT(07700000),
  // Frame 4
  B8_3BIT(00000000),
  B8_3BIT(07000000),
  B8_3BIT(77000000),
  B8_3BIT(70000000)
};
const uint8_t TetrisZMask[] =
{
  // Frame 1
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11000000),
  B8_1BIT(01100000),
  // Frame 2
  B8_1BIT(00000000),
  B8_1BIT(01000000),
  B8_1BIT(11000000),
  B8_1BIT(10000000),
  // Frame 3
  B8_1BIT(00000000),
  B8_1BIT(00000000),
  B8_1BIT(11000000),
  B8_1BIT(01100000),
  // Frame 4
  B8_1BIT(00000000),
  B8_1BIT(01000000),
  B8_1BIT(11000000),
  B8_1BIT(10000000)
};

#define TETRIS_SPR_WIDTH  4
#define TETRIS_SPR_HEIGHT 4
const uint8_t *TetrisSprData[] = { TetrisIData, TetrisJData, TetrisLData, TetrisOData, TetrisSData, TetrisTData, TetrisZData };//I : 1자 블록, J, L : 방향 다른 ㄱ블록, O : ㅁ블록, S, Z : 꾸불꾸불 불럭, T : ㅗ 블럭
const uint8_t *TetrisSprMask[] = { TetrisIMask, TetrisJMask, TetrisLMask, TetrisOMask, TetrisSMask, TetrisTMask, TetrisZMask};
const struct CRGB TetrisColours[] = { CRGB(0, 255, 255), CRGB(0, 0, 255), CRGB(255, 165, 0), CRGB(255, 255, 0), CRGB(50, 205, 50), CRGB(255, 0, 255), CRGB(255, 0, 0) };//테트리스 블럭 색 지정

uint8_t PlayfieldData[MATRIX_HEIGHT * ((MATRIX_WIDTH + 7) / 8) * _3BIT];
uint8_t PlayfieldMask[MATRIX_HEIGHT * ((MATRIX_WIDTH + 7) / 8) * _1BIT];
uint8_t CompletedLinesData[TETRIS_SPR_HEIGHT * ((MATRIX_WIDTH + 7) / 8) * _1BIT];
const struct CRGB CompletedLinesColour[] = { CRGB(255, 255, 255) }; //완성된 라인 색
cSprite Playfield, CompletedLines, CurrentBlock;
cLEDSprites Sprites(&leds);

unsigned char AttractMsg[144], GameOverMsg[88];
char BlankMsg[32];
cLEDText TetrisMsg;

uint8_t DropDelay;
boolean AttractMode, NextBlock;
int16_t TotalLines;
unsigned int HighScore = 0, LastScore, state = 0;


uint16_t PlasmaTime, PlasmaShift;
uint32_t LoopDelayMS, LastLoop;

//////////////////////////////////////////////////////
const int duration = 10000; //1초동안 채터링 현상을 무시, 1초동안 스위치를 아무리 눌러도 반응 안함
unsigned long pre_time = 0;
unsigned long cur_time = 0;
////////////////////////////////////////////////////// level 조정, 블럭 드랍 프레임 조정
#define GAME_STATE 14

void setup()
{
  Serial.begin(115200);
  //SerialBT.begin("Uno_test");
  mySerial.begin(115200, SERIAL_8N1, 34, 35);//RX : 34, TX : 35
  pinMode(GAME_STATE, LOW);

  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds[0], leds.Size());
  FastLED.setBrightness(10); //밝기
  FastLED.clear(true);
  FastLED.show();

  memset(PlayfieldData, 0, sizeof(PlayfieldData));
  memset(PlayfieldMask, 0, sizeof(PlayfieldMask));
  Playfield.Setup(leds.Width(), leds.Height(), PlayfieldData, 1, _3BIT, TetrisColours, PlayfieldMask);
  Playfield.SetPositionFrameMotionOptions(0, 0, 0, 0, 0, 0, 0, 0, 0);
  Sprites.AddSprite(&Playfield);

  memset(CompletedLinesData, 0, sizeof(CompletedLinesData));
  CompletedLines.Setup(leds.Width(), TETRIS_SPR_HEIGHT, CompletedLinesData, 1, _1BIT, CompletedLinesColour, CompletedLinesData);
  CompletedLines.SetPositionFrameMotionOptions(0, 0, 0, 0, 0, 0, 0, 0, 0);

  TetrisMsg.SetFont(MatriseFontData);
  sprintf((char *)BlankMsg, "%.*s", _min(((leds.Height() + TetrisMsg.FontHeight()) / (TetrisMsg.FontHeight() + 1)), (int)sizeof(BlankMsg) - 1), "                              ");
  sprintf((char *)AttractMsg, "%sTETRIS%sSCORE %u%sHIGH %u%sANY BUTTON TO START%s", BlankMsg, BlankMsg, LastScore, BlankMsg, (int)HighScore, BlankMsg, BlankMsg);
  TetrisMsg.Init(&leds, TetrisMsg.FontWidth() + 1, leds.Height(), (leds.Width() - TetrisMsg.FontWidth()) / 2, 0);
  TetrisMsg.SetBackgroundMode(BACKGND_LEAVE);
  TetrisMsg.SetScrollDirection(SCROLL_UP);
  TetrisMsg.SetTextDirection(CHAR_UP);
  TetrisMsg.SetFrameRate(1);
  TetrisMsg.SetOptionsChangeMode(INSTANT_OPTIONS_MODE);
  TetrisMsg.SetText(AttractMsg, strlen((const char *)AttractMsg));
  AttractMode = true;
  LoopDelayMS = TARGET_FRAME_TIME;
  LastLoop = millis() - LoopDelayMS;
  //  PlasmaShift = (random8(0, 5) * 32) + 64;
  //  PlasmaTime = 0;
  //  MsTimer2::set(2000,Level_Up);//2초 주기
  //  MsTimer2::start();
}

//////////////////////////////
void Level_Up() {
  cur_time = millis();
  if (cur_time - pre_time >= duration) {
    if (INITIAL_DROP_FRAMES > 10) { //
      INITIAL_DROP_FRAMES -= 5; //프레임 5씩 계속 다운
      pre_time = cur_time;
    }
    else
      pre_time = cur_time;
  }
}
////////////////////////////// 10초마다 프레임 5씩 드랍, 점점 빨라진다.

void loop()
{
  if (abs(millis() - LastLoop) >= LoopDelayMS)
  {
    LastLoop = millis();
    FastLED.clear();
    String str = String(HighScore) + "&" + String(LastScore) + "&" + String(state);
    //Serial.println(str);

    // Fill background with dim plasma 백그라운드 배경
    //    #define PLASMA_X_FACTOR  24
    //    #define PLASMA_Y_FACTOR  24
    //    for (int16_t x=0; x<MATRIX_WIDTH; x++)
    //    {
    //      for (int16_t y=0; y<MATRIX_HEIGHT; y++)
    //      {
    //        int16_t r = sin16(PlasmaTime) / 256;
    //        int16_t h = sin16(x * r * PLASMA_X_FACTOR + PlasmaTime) + cos16(y * (-r) * PLASMA_Y_FACTOR + PlasmaTime) + sin16(y * x * (cos16(-PlasmaTime) / 256) / 2);
    //        leds(x, y) = CHSV((uint8_t)((h / 256) + 128), 255, 64);
    //      }
    //    }
    //    uint16_t OldPlasmaTime = PlasmaTime;
    //    PlasmaTime += PlasmaShift;
    //    if (OldPlasmaTime > PlasmaTime)
    //      PlasmaShift = (random8(0, 5) * 32) + 64;

    if (AttractMode)
    {
      if (currentInput != NONE)
      {
        AttractMode = false;
        memset(PlayfieldData, 0, sizeof(PlayfieldData));
        memset(PlayfieldMask, 0, sizeof(PlayfieldMask));
        Sprites.RemoveSprite(&CurrentBlock);
        LastScore = 0;
        TotalLines = 0;
        DropDelay = INITIAL_DROP_FRAMES;
        CurrentBlock.SetXChange(-1);
        NextBlock = true;
        currentInput = NONE;
      }
    }
    else
    {
      Level_Up();//INITIAL_DROP_FRAMES 블럭 드롭 프레임, 낮으면 빨라진다.
      state = 1;//game start 상태 알림
      digitalWrite(GAME_STATE, HIGH);

      if (Sprites.IsSprite(&CompletedLines))  // We have highlighted complete lines, delay for visual effect
      {
        if (CompletedLines.GetXCounter() > 0)
          CompletedLines.SetXCounter(CompletedLines.GetXCounter() - 1);
        else
        {
          Sprites.RemoveSprite(&CompletedLines); //1줄 완성 시 해당 줄 삭제
          // Remove completed lines from playfield sprite
          uint8_t *Data = PlayfieldData;
          uint8_t *Mask = PlayfieldMask;
          uint16_t Mbpl = (MATRIX_WIDTH + 7) / 8;
          uint16_t Dbpl = Mbpl * _3BIT;
          int16_t k;
          for (int16_t i = (MATRIX_HEIGHT - 1) * Dbpl, j = (MATRIX_HEIGHT - 1) * Mbpl; i >= 0; i -= Dbpl, j -= Mbpl)
          {
            for (k = 0; k < MATRIX_WIDTH; k += 8)
            {
              if ((uint8_t)(0xff00 >> _min(MATRIX_WIDTH - k, 8)) != Mask[j + (k / 8)])
                break;
            }
            if (k >= MATRIX_WIDTH)
            {
              memmove(&Data[Dbpl], &Data[0], i);
              memset(&Data[0], 0, Dbpl);
              memmove(&Mask[Mbpl], &Mask[0], j);
              memset(&Mask[0], 0, Mbpl);
              i += Dbpl;
              j += Mbpl;
            }
          }
        }
      }
      else
      {
        if (CurrentBlock.GetXChange() >= 0) // We have a current block
        {
          // Check for user input
          if ( currentInput == ROTATE )//블럭 회전
          {
            Serial.println(CurrentBlock.GetXChange());
            currentInput = NONE;
            if ((CurrentBlock.GetCurrentFrame() % 2) == 1)
            {
              if (CurrentBlock.GetXChange() == 0)
                CurrentBlock.m_X = _min(CurrentBlock.m_X, MATRIX_WIDTH - TETRIS_SPR_WIDTH);
              else if ((CurrentBlock.GetXChange() != 3) && (CurrentBlock.GetFlags() & SPRITE_EDGE_X_MAX))
                --CurrentBlock.m_X;
            }
            CurrentBlock.IncreaseFrame();
            Sprites.DetectCollisions(&CurrentBlock);
            if (CurrentBlock.GetFlags() & SPRITE_COLLISION)
              CurrentBlock.DecreaseFrame();
          }

          if ( currentInput == LEFT && (! (CurrentBlock.GetFlags() & SPRITE_EDGE_X_MIN)) ) //블럭 왼쪽 이동
          {
            currentInput = NONE;
            CurrentBlock.m_X--;
            Sprites.DetectCollisions(&CurrentBlock);
            if (CurrentBlock.GetFlags() & SPRITE_COLLISION)//COLLISION : 충돌, 블럭 충돌되면
              CurrentBlock.m_X++;
          }

          else if ( currentInput == RIGHT && (! (CurrentBlock.GetFlags() & SPRITE_EDGE_X_MAX)) )//블럭 오른쪽 이동
          {
            currentInput = NONE;
            CurrentBlock.m_X++;
            Sprites.DetectCollisions(&CurrentBlock);
            if (CurrentBlock.GetFlags() & SPRITE_COLLISION)
              CurrentBlock.m_X--;
          }

          if ( currentInput == DOWN )
          {
            currentInput = NONE;
            CurrentBlock.SetYCounter(1);
          }

          // Do block checks for bottom or collision
          if (CurrentBlock.GetYCounter() <= 1)
          {
            if (CurrentBlock.GetFlags() & SPRITE_EDGE_Y_MIN)
              NextBlock = true;
            else
            {
              --CurrentBlock.m_Y;
              Sprites.DetectCollisions(&CurrentBlock);
              ++CurrentBlock.m_Y;
              if (CurrentBlock.GetFlags() & SPRITE_COLLISION)
              {
                // Block has collided check for game over
                int16_t MaxY = MATRIX_HEIGHT - 2;
                if ((CurrentBlock.GetCurrentFrame() % 2) == 1)
                {
                  if (CurrentBlock.GetXChange() == 0)
                    MaxY -= 2;
                  else if (CurrentBlock.GetXChange() != 3)
                    MaxY -= 1;
                }
                else if (CurrentBlock.GetXChange() == 0)
                  ++MaxY;
                if (CurrentBlock.m_Y < MaxY)
                  NextBlock = true;
                else
                {
                  // Game over
                  state = 0; //게임오버 상태 알림
                  digitalWrite(GAME_STATE, LOW);
                  INITIAL_DROP_FRAMES = 40; //드랍 프레임 초기화

                  CurrentBlock.SetYCounter(2);  // Stop last block moving down!
                  AttractMode = true;
                  if (LastScore > HighScore)
                  {
                    HighScore = LastScore;
                    sprintf((char *)GameOverMsg, "%sGAME OVER%sNEW HIGH SCORE %u%s", BlankMsg, BlankMsg, LastScore, BlankMsg);
                    //Serial.println(HighScroe);
                  }
                  else
                    sprintf((char *)GameOverMsg, "%sGAME OVER%sSCORE %u%s", BlankMsg, BlankMsg, LastScore, BlankMsg);
  
                  sprintf((char *)AttractMsg, "%sTETRIS%sSCORE %u%sHIGH %u%sANY BUTTON TO START%s", BlankMsg, BlankMsg, LastScore, BlankMsg, HighScore, BlankMsg, BlankMsg);
                  TetrisMsg.SetText(GameOverMsg, strlen((char *)GameOverMsg));
                  TetrisMsg.SetBackgroundMode(BACKGND_DIMMING, 0x40);
                }
              }
            }
          }
        }
        if (NextBlock)  // Start new block // NextBlock 값이 True일 때
        {
          state = 1;
          if (CurrentBlock.GetXChange() >= 0) // We have a current block so add to playfield before creating new block
          {
            Playfield.Combine(CurrentBlock.m_X, CurrentBlock.m_Y, &CurrentBlock);
            Sprites.RemoveSprite(&CurrentBlock);
            // Make completed lines highlight sprite & score
            memset(CompletedLinesData, 0, sizeof(CompletedLinesData));
            CompletedLines.m_Y = -1;
            uint8_t *Mask = PlayfieldMask;
            uint16_t Mbpl = (MATRIX_WIDTH + 7) / 8;
            int16_t j, numlines = 0;
            for (int16_t i = (MATRIX_HEIGHT - 1) * Mbpl, y = 0; i >= 0; i -= Mbpl, ++y)
            {
              for (j = 0; j < MATRIX_WIDTH; j += 8)
              {
                if ((uint8_t)(0xff00 >> _min(MATRIX_WIDTH - j, 8)) != Mask[i + (j / 8)])
                  break;
              }
              if (j >= MATRIX_WIDTH)
              {
                if (CompletedLines.m_Y == -1)
                  CompletedLines.m_Y = y;
                memset(&CompletedLinesData[((TETRIS_SPR_HEIGHT - 1) - (y - CompletedLines.m_Y)) * Mbpl], 0xff, Mbpl);
                numlines++;
              }
            }
            if (numlines > 0)
            {
              CompletedLines.SetXCounter(15);  // Set delay for highlight display to 15 loops
              Sprites.AddSprite(&CompletedLines);
            }
            LastScore += 1;
            if (numlines == 1)
              LastScore += 4;
            else if (numlines == 2)
              LastScore += 12;
            else if (numlines == 3)
              LastScore += 20;
            else if (numlines == 4)
              LastScore += 40;
            TotalLines += numlines;
            DropDelay = _max(1, INITIAL_DROP_FRAMES - (TotalLines / 5));
          }
          // Start new block
          uint8_t j = random8(sizeof(TetrisSprData) / sizeof(TetrisSprData[0]));
          CurrentBlock.Setup(TETRIS_SPR_WIDTH, TETRIS_SPR_WIDTH, TetrisSprData[j], 4, _3BIT, TetrisColours, TetrisSprMask[j]);
          CurrentBlock.SetPositionFrameMotionOptions((MATRIX_WIDTH / 2) - 1, MATRIX_HEIGHT, 0, 0, 0, 0, -1, DropDelay, SPRITE_DETECT_COLLISION | SPRITE_DETECT_EDGE);
          CurrentBlock.SetXChange(j);
          Sprites.AddSprite(&CurrentBlock);
          NextBlock = false;
        }
        Sprites.UpdateSprites();
      }
    }
    Sprites.RenderSprites();
    if (AttractMode)
    {
      if (TetrisMsg.UpdateText() == -1)
      {
        TetrisMsg.SetText(AttractMsg, strlen((char *)AttractMsg));
        TetrisMsg.SetBackgroundMode(BACKGND_LEAVE);
        Sprites.RemoveSprite(&CurrentBlock);
        memset(PlayfieldData, 0, sizeof(PlayfieldData));
        memset(PlayfieldMask, 0, sizeof(PlayfieldMask));
      }
    }
    FastLED.show();
  }
  if (mySerial.available() > 0) {

    char keyPress = mySerial.read(); //조이스틱 값 받아 옴
    //    Serial.println("data : "+keyPress);
    switch (keyPress) {
      case 'w':
        currentInput = ROTATE; //모양 변경
        break;
      case 'a':
        currentInput = LEFT; //왼쪽 이동
        break;
      case 's':
        currentInput = DOWN; //아래로 이동
        break;
      case 'd':
        currentInput = RIGHT; //오른쪽으로 이동
        break;
    }
    //    Serial.print("data is : ");
    //    Serial.println(currentInput);
  }


}
