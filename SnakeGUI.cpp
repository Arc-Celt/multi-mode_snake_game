#include "includes.h"
#include "SnakeGUI.h"
#include "Snake.h"

//SnakeGUI.cpp用于存放UI绘制、音乐加载等代码

//------------------------------------------------------GUI-----------------------------------------------


    int windowHeight = BOXY*NUMY,windowWidth = BOXX*NUMX;
	int xMouse = 0, yMouse = 0;
	int xSearched = -1, ySearched = -1;
	unsigned int idSearched = BUTTON_ID_ZERO;
	bool redraw = true;

    int buttonNum = BUTTON_SIZE;
    // 按下按钮ID
    int pressButtonId   = BUTTON_ID_ZERO;
    int hoveredButtonId = BUTTON_ID_ZERO;
    int focusedButtonId = BUTTON_ID_ZERO;
	MUSIC music;


//绘制主界面
int PrintMenu()
{

	//创建图片对象
	PIMAGE title1 = newimage();	
    PIMAGE picture1 = newimage();
	//从文件中获取图像（和原图一样大小），输入实际的图像文件路径
	//例如, getimage(pimg, "E:/博客写作/博客专栏/EGE/鬼刀.png");
	getimage(title1, "resource/title.png");	
    getimage(picture1, "resource/bigsnake.jpg");
    //if (openmusicfile("resourse/music/BGM.mp3",1) == 1){
    //----------------音乐-----------------------------
    openmusicfile("resource/music/button.mp3",0);
    openmusicfile("resource/music/eat.mp3",1);
    openmusicfile("resource/music/death.mp3",2);
    openmusicfile("resource/music/endgame.mp3",3);


	for (; is_run(); delay_fps(60)) {
//-----------------贴图-------------------------------
	
	putimage(BOXX*NUMX/2-200, 100, title1);
	putimage(BOXX*NUMX-250, BOXY*NUMY-270, picture1);

//----------------按钮-----------------------------

    initAllButtons();
    draw();

		bool mouseMoved = false;

		while (mousemsg()) {
			mouse_msg msg = getmouse();

			// 判断鼠标左键按下（左键按下确定位置，同时判断是否为按钮区域
			// 抬起则解除按下状态
			if (msg.is_left()) {
				if (msg.is_down()) {
					
					int btnId = BUTTON_ID_ZERO;

					// 检查位置对应的按钮ID
					btnId = searchButton(msg.x, msg.y);
					 
					if ((btnId != BUTTON_ID_ZERO) && (findButton(btnId)->state.enable)) {
						// 将被按下的按钮设置为按下状态
						if (btnId != BUTTON_ID_ZERO) {
							pressButtonId = btnId;
							findButton(pressButtonId)->state.pressed = true;
							redraw = true;
						}
					}
                    return pressButtonId;
				}
				else {
					//左键抬起，如果有按钮被按下
					if (pressButtonId != BUTTON_ID_ZERO) {
						unsigned btnId = pressButtonId;
						CircleButton* button = findButton(btnId);
						
						// 取消之前按钮的焦点状态
						findButton(focusedButtonId)->state.focused = false;

						//设置当前按钮为焦点状态
						button->state.focused = true;
						focusedButtonId = btnId;

						// 解除按下状态
						button->state.pressed = false;
						pressButtonId = BUTTON_ID_ZERO;
						
						// 切换选中
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

		//当鼠标移动
		if (mouseMoved) {
			//查找悬停的按钮
			int btnId = searchButton(xMouse, yMouse);

			// 悬停按钮改变
			if (btnId != hoveredButtonId) {
				// 标记原先的按钮为非悬停状态
				if (hoveredButtonId != BUTTON_ID_ZERO) {
					findButton(hoveredButtonId)->state.hovered = false;
				}

				// 标记当前悬停的按钮为悬停状态
				if (btnId != BUTTON_ID_ZERO) {
					findButton(btnId)->state.hovered = true;
				}

				hoveredButtonId = btnId;
				redraw = true;
			}
		}

		// 判断是否需要重绘，减少不必要的绘制操作
		if (redraw) {
			cleardevice();
			draw();
			redraw = false;

            //绘制图像，(0, 0)是图片绘制区域的左上角	 
            putimage(BOXX*NUMX/2-200, 100, title1);
		}
	}
    //如果后面不用了的话就销毁图像，释放内存(图像是动态分配的，避免内存泄漏)
	delimage(title1);

    // music[0].Play(0);
    return pressButtonId;
}

//启动模式1(单人模式)
void playmodel1()
{
    GameControl_single();
}

//启动模式2(双人模式)
void playmodel2()
{
    GameControl_double();
}

//启动模式3(穿墙模式)
void playmodel3()
{
    GameControl_passwall();
}

//启动模式4(随机墙体模式)
void playmodel4()
{
    GameControl_randwall();
}

//------------按钮相关函数定义------------
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

// 绘制按钮
void drawButton(const CircleButton* button)
{
	if (button != NULL) {
		if (button->state.visible == true) {
			setfillcolor(EGEARGB(0xFF, 0x1E, 0x90, 0xFF));
			setcolor(WHITE);
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			setfont(24, 0, "");

			//根据状态进行不同的绘制
			color_t color;
            //选择颜色
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

			// 绘制按钮
			ege_fillellipse(button->x - button->radius, button->y - button->radius, 2 * button->radius, 2 * button->radius);

			// 选中则绘制外环边框
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
            //不可见按钮的展示
			setcolor(BLACK);
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			setfont(24, 0, "");
			xyprintf(button->x, button->y, "");
		}
	}
}


// 绘制所有按钮
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
			break;   //退出，已经检测到，后面的按钮不再检测
		}
	}
	return buttonId;
}

void draw()
{
	//绘制
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

    //设置按钮xy
	for (int i = 0; i < buttonNum; i++) {
		int id = BUTTON_MIN_ID + i;
        int x = (int)(BOXX*NUMX*0.6/2);
        int y = (int)(i*BOXY*5+200);
		initButton(findButton(id), x, y, 20);
	}

    //个性化修改按钮状态
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
//     int out  = 0;//判断是否顺利
// 	//检查是否打开
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
//     int out  = 0;//判断是否顺利
// 	//检查是否打开
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
// 	setfont(40, 0, "楷体");

// 	MUSIC music;

// 	music.OpenFile("resource/music/death.mp3");
	
// 	//检查是否打开
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