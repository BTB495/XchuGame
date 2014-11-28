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
int Xchu_Status[Xchu_MAX];//0�Ŏ�.1�Ő�.2�ł܂܂�

//�v���O�����N������1�x�������s
//�V�X�e���ݒ�Ȃǂ��s��
void SystemInit( void )
{
  MikanWindow->SetWindowName( "�Q�[���^�C�g��" );

  MikanWindow->SetWindowSize(288, 288);
}

//MainLoop�J�n�O��1�x�������s
//�e�N�X�`���̓ǂݍ��݂Ȃǂ̃Q�[���J�n�O�̏������s��
void UserInit( void )
{
	MikanDraw->CreateTexture(0,"GX.png",TRC_ZERO);
	MikanDraw->CreateTexture(1,"BX.png",TRC_ZERO);
	MikanDraw->CreateTexture(2,"PX.png",TRC_ZERO);
	MikanDraw->CreateTexture(3,"UX.png",TRC_ZERO);
	MikanDraw->CreateTexture(4,"Item.png",TRC_ZERO);
	MikanDraw->CreateFont(0, 30, 0xFFFFFFFF);
	//�����̂��߂̃R�[�h
	srand((unsigned int)time(NULL));
}

//1�b�Ԃ�60����s
//0��Ԃ��Ă���Ԃ͉��x�ł����s�����
int MainLoop( void )
{
	//��ʃN���A�B
	MikanDraw->ClearScreen();
	
	//�}�E�X�̍��W�擾
	MouseX = MikanInput->GetMousePosX();
	MouseY = MikanInput->GetMousePosY();

	//�g��`��
	MikanDraw->DrawTextureScaling(4, 0, 0, 0, 16, 96, 112, 3.0, 0);

	//�G�b�N���オ����ł��烉���_���ȐF�Ő����Ԃ点��
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
		//���N���b�N�ŃJ�[�\�����G�b�N����Əd�Ȃ��Ă�����
		if (MikanInput->GetMouseNum(0)==1 && (((XchuX[i]-MouseX)*(XchuX[i]-MouseX))+((XchuY[i]-MouseY)*(XchuY[i]-MouseY)))<=(XchuW/2)*(XchuW/2) )
		{
			//�G�b�N������܂܂��Ԃ�			
			Xchu_Status[i] = 2;
			break;
		}else if(MikanInput->GetMouseNum(0)==0){
			//�����łȂ���ΐ����Ă�����
			Xchu_Status[i] = 1;
		}
	}

	//�G�b�N����̕`��
	for(int i=0; i<Xchu_MAX; i=i+1)
	{
		//�G�b�N���オ�����Ă�����g�̒��ɕ`��
		if(Xchu_Status[i] == 1)
		{
			int ix = i%4;
			int iy = i/4;
			XchuX[i] = 54*ix+63;
			XchuY[i] = 54*iy+63;
			MikanDraw->DrawTextureScalingC(XchuC[i], XchuX[i], XchuY[i], 0, 0, 16, 16, 3.0, 0);
		}
		//�܂܂�Ă�����}�E�X�̈ʒu�ɕ`��
		if(Xchu_Status[i] == 2)
		{
			XchuX[i] = MouseX;
			XchuY[i] = MouseY;
			MikanDraw->DrawTextureScalingC(XchuC[i], XchuX[i], XchuY[i], 0, 0, 16, 16, 3.0, 0);
		}
	}

	for(int i=0; i<Xchu_MAX; i=i+1)
	{
		//�G�b�N��������n������X�R�A��+1���ăG�b�N������E��
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

	//�X�R�A�̕`��
	MikanDraw->Printf( 0, 257, 3, "%d",GX );
	MikanDraw->Printf( 0, 257, 257, "%d",BX );
	MikanDraw->Printf( 0, 2, 257, "%d",UX );
	MikanDraw->Printf( 0, 2, 3, "%d",PX );

	//esc�ŏI��
	return MikanInput->GetKeyNum( K_ESC ) == 1;
}

//MainLoop�I�����1�x�������s
//��Еt���Ȃǂ��s��
void CleanUp( void )
{
}
