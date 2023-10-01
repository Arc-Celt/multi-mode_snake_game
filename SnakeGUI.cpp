#include "includes.h"
#include "SnakeGUI.h"
#include "Snake.h"

//SnakeGUI.cpp���ڴ��UI���ơ����ּ��صȴ���

//------------------------------------------------------GUI-----------------------------------------------


    int windowHeight = BOXY*NUMY,windowWidth = BOXX*NUMX;
	int xMouse = 0, yMouse = 0;
	int xSearched = -1, ySearched = -1;
	unsigned int idSearched = BUTTON_ID_ZERO;
	bool redraw = true;

    int buttonNum = BUTTON_SIZE;
    // ���°�ťID
    int pressButtonId   = BUTTON_ID_ZERO;
    int hoveredButtonId = BUTTON_ID_ZERO;
    int focusedButtonId = BUTTON_ID_ZERO;
	MUSIC music;


//����������
int PrintMenu()
{

	//����ͼƬ����
	PIMAGE title1 = newimage();	
    PIMAGE picture1 = newimage();
	//���ļ��л�ȡͼ�񣨺�ԭͼһ����С��������ʵ�ʵ�ͼ���ļ�·��
	//����, getimage(pimg, "E:/����д��/����ר��/EGE/��.png");
	getimage(title1, "resource/title.png");	
    getimage(picture1, "resource/bigsnake.jpg");
    //if (openmusicfile("resourse/music/BGM.mp3",1) == 1){
    //----------------����-----------------------------
    openmusicfile("resource/music/button.mp3",0);
    openmusicfile("resource/music/eat.mp3",1);
    openmusicfile("resource/music/death.mp3",2);
    openmusicfile("resource/music/endgame.mp3",3);


	for (; is_run(); delay_fps(60)) {
//-----------------��ͼ-------------------------------
	
	putimage(BOXX*NUMX/2-200, 100, title1);
	putimage(BOXX*NUMX-250, BOXY*NUMY-270, picture1);

//----------------��ť-----------------------------

    initAllButtons();
    draw();

		bool mouseMoved = false;

		while (mousemsg()) {
			mouse_msg msg = getmouse();

			// �ж����������£��������ȷ��λ�ã�ͬʱ�ж��Ƿ�Ϊ��ť����
			// ̧����������״̬
			if (msg.is_left()) {
				if (msg.is_down()) {
					
					int btnId = BUTTON_ID_ZERO;

					// ���λ�ö�Ӧ�İ�ťID
					btnId = searchButton(msg.x, msg.y);
					 
					if ((btnId != BUTTON_ID_ZERO) && (findButton(btnId)->state.enable)) {
						// �������µİ�ť����Ϊ����״̬
						if (btnId != BUTTON_ID_ZERO) {
							pressButtonId = btnId;
							findButton(pressButtonId)->state.pressed = true;
							redraw = true;
						}
					}
                    return pressButtonId;
				}
				else {
					//���̧������а�ť������
					if (pressButtonId != BUTTON_ID_ZERO) {
						unsigned btnId = pressButtonId;
						CircleButton* button = findButton(btnId);
						
						// ȡ��֮ǰ��ť�Ľ���״̬
						findButton(focusedButtonId)->state.focused = false;

						//���õ�ǰ��ťΪ����״̬
						button->state.focused = true;
						focusedButtonId = btnId;

						// �������״̬
						button->state.pressed = false;
						pressButtonId = BUTTON_ID_ZERO;
						
						// �л�ѡ��
						if (button->state.checkable)
							button->state.checked = !(button->state.checked);
						
						redraw = true;
					}
				}
			}
			else if (msg.is_move()) {
				mouseMoved = true;
				xMouse = msg.x;
				yMouse = msg.y;
			}
		}

		//������ƶ�
		if (mouseMoved) {
			//������ͣ�İ�ť
			int btnId = searchButton(xMouse, yMouse);

			// ��ͣ��ť�ı�
			if (btnId != hoveredButtonId) {
				// ���ԭ�ȵİ�ťΪ����ͣ״̬
				if (hoveredButtonId != BUTTON_ID_ZERO) {
					findButton(hoveredButtonId)->state.hovered = false;
				}

				// ��ǵ�ǰ��ͣ�İ�ťΪ��ͣ״̬
				if (btnId != BUTTON_ID_ZERO) {
					findButton(btnId)->state.hovered = true;
				}

				hoveredButtonId = btnId;
				redraw = true;
			}
		}

		// �ж��Ƿ���Ҫ�ػ棬���ٲ���Ҫ�Ļ��Ʋ���
		if (redraw) {
			cleardevice();
			draw();
			redraw = false;

            //����ͼ��(0, 0)��ͼƬ������������Ͻ�	 
            putimage(BOXX*NUMX/2-200, 100, title1);
		}
	}
    //������治���˵Ļ�������ͼ���ͷ��ڴ�(ͼ���Ƕ�̬����ģ������ڴ�й©)
	delimage(title1);

    // music[0].Play(0);
    return pressButtonId;
}

//����ģʽ1(����ģʽ)
void playmodel1()
{
    GameControl_single();
}

//����ģʽ2(˫��ģʽ)
void playmodel2()
{
    GameControl_double();
}

//����ģʽ3(��ǽģʽ)
void playmodel3()
{
    GameControl_passwall();
}

//����ģʽ4(���ǽ��ģʽ)
void playmodel4()
{
    GameControl_randwall();
}

//------------��ť��غ�������------------
bool insideButton(const CircleButton* button, int x, int y)
{
	int dx = x - button->x, dy = y - button->y;
	return (dx * dx + dy * dy) <= (button->radius * button->radius);
}

unsigned int generateId()
{
	static unsigned int id = 0;
	return ++id;
}

CircleButton* findButton(unsigned int id)
{
	return &buttonArray[id];
}

unsigned int getButtonId(const CircleButton* button)
{
	return button->id;
}

// ���ư�ť
void drawButton(const CircleButton* button)
{
	if (button != NULL) {
		if (button->state.visible == true) {
			setfillcolor(EGEARGB(0xFF, 0x1E, 0x90, 0xFF));
			setcolor(WHITE);
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			setfont(24, 0, "");

			//����״̬���в�ͬ�Ļ���
			color_t color;
            //ѡ����ɫ
			if (!(button->state.enable)) {
				color = DARKGRAY;
			}
			else
			{
				if (button->state.pressed) {
					color = button->pressedColor;
				}
				else {
					color = button->normalColor;
				}

				if (button->state.hovered) {
					color = interpColor(color, BLACK, 0.125f);
				} 
			}

			setfillcolor(color);

			// ���ư�ť
			ege_fillellipse(button->x - button->radius, button->y - button->radius, 2 * button->radius, 2 * button->radius);

			// ѡ��������⻷�߿�
			if (button->state.focused)
			{
				setcolor(interpColor(color, BLACK, 0.25f));
				setlinewidth(4);

				int borderRadius = button->radius + 4;

				ege_ellipse(button->x - borderRadius, button->y - borderRadius, 2 * borderRadius, 2 * borderRadius);
			}


			int radiusCheckBox = 14;
			int xCheckBox = button->x - button->radius - 2 * radiusCheckBox;
			int yCheckBox = button->y;

			if (button->state.checked) {
				setfillcolor(button->pressedColor);
				ege_fillellipse(xCheckBox - radiusCheckBox, yCheckBox - radiusCheckBox,2 * radiusCheckBox, 2 * radiusCheckBox);
			}
			else {
				setcolor(button->pressedColor);
				setlinewidth(2);
				ege_ellipse(xCheckBox - radiusCheckBox, yCheckBox - radiusCheckBox, 2 * radiusCheckBox, 2 * radiusCheckBox);
			}

			setcolor(BLACK);
			xyprintf(button->x+100, button->y, "%s", button->text);
		}
		else {
            //���ɼ���ť��չʾ
			setcolor(BLACK);
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			setfont(24, 0, "");
			xyprintf(button->x, button->y, "");
		}
	}
}


// �������а�ť
void drawAllButtons()
{
	for (int i = 0; i < buttonNum; i++) {
		unsigned int btnId = BUTTON_MIN_ID + i;
		drawButton(findButton(btnId));
	}
}

int searchButton(int x, int y)
{
	int buttonId = BUTTON_ID_ZERO;

	for (int i = 0; i < buttonNum; i++) {
		unsigned int btnId = BUTTON_MIN_ID + i;
		CircleButton* button = findButton(btnId);

		if ((button != NULL) && (insideButton(button, x, y))) {
			buttonId = btnId;
			break;   //�˳����Ѿ���⵽������İ�ť���ټ��
		}
	}
	return buttonId;
}

void draw()
{
	//����
	drawAllButtons();
	setcolor(BLACK);
	setfont(24, 0, "");
	settextjustify(LEFT_TEXT, TOP_TEXT);
}

color_t interpColor(color_t colorA, color_t colorB, float t)
{
	if (t > 1)
		t = 1;
	else if (t < 0)
		t = 0;

	int r = roundf((1 - t) * EGEGET_R(colorA) + t * EGEGET_R(colorB));
	int g = roundf((1 - t) * EGEGET_G(colorA) + t * EGEGET_G(colorB));
	int b = roundf((1 - t) * EGEGET_B(colorA) + t * EGEGET_B(colorB));

	return EGERGB(r, g, b);
}


void initButtonState(CircleButton* button)
{
	button->state.enable = true;
	button->state.visible = true;
	button->state.pressed = false;
	button->state.checkable = true;
	button->state.checked = false;
	button->state.hovered = false;
	button->state.focused = false;
}

void initButton(CircleButton* button, int x, int y, int radius)
{
	if (button != NULL) {
		button->id = generateId();
		button->x = x;
		button->y = y;
		button->radius = radius;
		button->normalColor  = EGEARGB(0xFF, 0x40, 0xE0, 0xD0);
		button->pressedColor = EGEARGB(0xFF, 0x1E, 0x90, 0xFF);
		strcpy(button->text,"Button");

		initButtonState(button);
	}
}

void initAllButtons()
{
	int colNum = 2;

    //���ð�ťxy
	for (int i = 0; i < buttonNum; i++) {
		int id = BUTTON_MIN_ID + i;
        int x = (int)(BOXX*NUMX*0.6/2);
        int y = (int)(i*BOXY*5+200);
		initButton(findButton(id), x, y, 20);
	}

    //���Ի��޸İ�ť״̬
	CircleButton* btn;
	btn = findButton(BUTTON_MIN_ID);
	btn->state.enable = false;
    btn->state.visible = false;

	btn = findButton(BUTTON_MIN_ID + 1);
	strcpy(btn->text,"1 PLAYER");
    //btn->state.visible = true;
    btn = findButton(BUTTON_MIN_ID + 2);
    strcpy(btn->text,"2 PLAYERS");
    
    btn = findButton(BUTTON_MIN_ID + 3);

    strcpy(btn->text,"FREE MODEL");
    btn = findButton(BUTTON_MIN_ID + 4);
    strcpy(btn->text,"WALL MODEL");
    
    btn = findButton(BUTTON_MIN_ID + 5);
    strcpy(btn->text,"QUIT");

}

// int openmusicfile(char *s,int num){
//     int out  = 0;//�ж��Ƿ�˳��
// 	//����Ƿ��
//     music[num].OpenFile(s);
	
// 	if (music[num].IsOpen())
// 	{
// 		xyprintf(200, 220, "%s\n", "success");
//         out = 1;
// 	}
// 	else
// 	{
// 		xyprintf(200, 220, "%s\n", "failure");  
// 	}
//     return out;
// }


// int closemusicplay(int num){
//     int out  = 0;//�ж��Ƿ�˳��
// 	//����Ƿ��
// 	if (music[num].IsOpen())
// 	{
// 		xyprintf(200, 220, "%s\n", "music closed success");
// 	    music[num].Close();
//         out = 1;
// 	}
// 	else
// 	{
// 		xyprintf(200, 220, "%s\n", "music closed failure");
	
//     return out;
//     }
// }

// int main()
// {
// 	initgraph(640, 480, 0);
// 	setbkcolor(WHITE);
// 	setcolor(BLACK);
// 	setfont(40, 0, "����");

// 	MUSIC music;

// 	music.OpenFile("resource/music/death.mp3");
	
// 	//����Ƿ��
// 	if (music.IsOpen())
// 	{
// 		xyprintf(200, 220, "%s\n", "success");
// 		music.Play();
// 	}
// 	else
// 	{
// 		xyprintf(200, 220, "%s\n", "failure");
// 	}
	
// 	getch();

// 	music.Close();

// 	closegraph();

// 	return 0;
// }