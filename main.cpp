#include <Mikan.h>
#include <stdlib.h>
#include <time.h>

int MouseX;
int MouseY;
const int Xchu_MAX=16;
int XchuX[Xchu_MAX];
int XchuY[Xchu_MAX];
int XchuC[Xchu_MAX];
int XchuW=48;
int XchuH=48;
int GX=0;
int BX=0;
int UX=0;
int PX=0;
int Xchu_Status[Xchu_MAX];//0で死.1で生.2でつままれ

//プログラム起動時に1度だけ実行
//システム設定などを行う
void SystemInit( void )
{
  MikanWindow->SetWindowName( "ゲームタイトル" );

  MikanWindow->SetWindowSize(288, 288);
}

//MainLoop開始前に1度だけ実行
//テクスチャの読み込みなどのゲーム開始前の準備を行う
void UserInit( void )
{
	MikanDraw->CreateTexture(0,"GX.png",TRC_ZERO);
	MikanDraw->CreateTexture(1,"BX.png",TRC_ZERO);
	MikanDraw->CreateTexture(2,"PX.png",TRC_ZERO);
	MikanDraw->CreateTexture(3,"UX.png",TRC_ZERO);
	MikanDraw->CreateTexture(4,"Item.png",TRC_ZERO);
	MikanDraw->CreateFont(0, 30, 0xFFFFFFFF);
	//乱数のためのコード
	srand((unsigned int)time(NULL));
}

//1秒間に60回実行
//0を返している間は何度でも実行される
int MainLoop( void )
{
	//画面クリア。
	MikanDraw->ClearScreen();
	
	//マウスの座標取得
	MouseX = MikanInput->GetMousePosX();
	MouseY = MikanInput->GetMousePosY();

	//枠を描画
	MikanDraw->DrawTextureScaling(4, 0, 0, 0, 16, 96, 112, 3.0, 0);

	//エックちゅが死んでたらランダムな色で生き返らせる
	for(int i=0; i<Xchu_MAX; i=i+1)
	{
		if(Xchu_Status[i] == 0 )
		{
			Xchu_Status[i] = 1;
			XchuC[i] = rand()%4;
		}
	}


	for(int i=0; i<Xchu_MAX; i=i+1)
	{
		//左クリックでカーソルがエックちゅと重なっていたら
		if (MikanInput->GetMouseNum(0)==1 && (((XchuX[i]-MouseX)*(XchuX[i]-MouseX))+((XchuY[i]-MouseY)*(XchuY[i]-MouseY)))<=(XchuW/2)*(XchuW/2) )
		{
			//エックちゅをつままれ状態に			
			Xchu_Status[i] = 2;
			break;
		}else if(MikanInput->GetMouseNum(0)==0){
			//そうでなければ生きている状態
			Xchu_Status[i] = 1;
		}
	}

	//エックちゅの描画
	for(int i=0; i<Xchu_MAX; i=i+1)
	{
		//エックちゅが生きていたら枠の中に描画
		if(Xchu_Status[i] == 1)
		{
			int ix = i%4;
			int iy = i/4;
			XchuX[i] = 54*ix+63;
			XchuY[i] = 54*iy+63;
			MikanDraw->DrawTextureScalingC(XchuC[i], XchuX[i], XchuY[i], 0, 0, 16, 16, 3.0, 0);
		}
		//つままれていたらマウスの位置に描画
		if(Xchu_Status[i] == 2)
		{
			XchuX[i] = MouseX;
			XchuY[i] = MouseY;
			MikanDraw->DrawTextureScalingC(XchuC[i], XchuX[i], XchuY[i], 0, 0, 16, 16, 3.0, 0);
		}
	}

	for(int i=0; i<Xchu_MAX; i=i+1)
	{
		//エックちゅを収穫したらスコアを+1してエックちゅを殺す
		if(MikanInput->GetMouseNum(0)<0 && MouseY<36 && Xchu_Status[i] == 2 && XchuC[i] == 0)
		{
			GX = GX +1;
			Xchu_Status[i] = 0;
		}
		if(MikanInput->GetMouseNum(0)<0 && 252<MouseX && Xchu_Status[i] == 2 && XchuC[i] == 1)
		{
			BX = BX +1;
			Xchu_Status[i] = 0;
		}
		if(MikanInput->GetMouseNum(0)<0 && MouseX<36 && Xchu_Status[i] == 2 && XchuC[i] == 2)
		{
			PX = PX +1;
			Xchu_Status[i] = 0;
		}
		if(MikanInput->GetMouseNum(0)<0 && 252<MouseY && Xchu_Status[i] == 2 && XchuC[i] == 3)
		{
			UX = UX +1;
			Xchu_Status[i] = 0;
		}		
	}

	//スコアの描画
	MikanDraw->Printf( 0, 257, 3, "%d",GX );
	MikanDraw->Printf( 0, 257, 257, "%d",BX );
	MikanDraw->Printf( 0, 2, 257, "%d",UX );
	MikanDraw->Printf( 0, 2, 3, "%d",PX );

	//escで終了
	return MikanInput->GetKeyNum( K_ESC ) == 1;
}

//MainLoop終了後に1度だけ実行
//後片付けなどを行う
void CleanUp( void )
{
}
