//
//  "$Id: dahua_aew.h 513 2010-04-26 01:21:14Z wang_jun $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:	
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef _DAHUA_AEW_H_
#define _DAHUA_AEW_H_

#include <asm-arm/arch-davinci/dm365_ipipe.h>

typedef struct COLOR_PARAM
{
	int	brightness;	// 0-100
	int contrast;	// 0-100
	int	hue;		// 0-100
	int saturation;	// 0-100
}COLOR_PARAM;

typedef enum WB_MODE
{
	WB_DISABLE,			// ��ֹ
	WB_AUTO,			// �Զ�
	WB_DAYLIGHT,		// �չ� 6500k
	WB_CLOUDY,			// ���� 7500k
	WB_INCANDESCENCE,	// ���ȹ� 5000k
	WB_FLUORESCENT,		// �չ�� 4400k
	WB_TUNGSTEN			// ��˿�� 2800k
}WB_MODE;

typedef struct AEW_WINDOW
{
	int width;			// ���ڿ��
	int height;			// ���ڸ߶�
	int start_x;		// ����x��ʼ����
	int start_y;		// ����y��ʼ����
}AEW_WINDOW;

typedef enum DNC_MODE
{
	DNC_MULTICOLOR,		// ��ɫ
	DNC_AUTO,			// �Զ��л�
	DNC_BLACKWHITE,		// ǿ��Ϊ�ڰ�ģʽ
}DNC_MODE;

typedef enum VSTD
{
	VSTD_PAL,
	VSTD_NTSC,
	VSTD_SECAM,
	VSTD_NR
}VSTD;
typedef enum FE_AD
{
	AD_NONE,
	AD_9920,
	AD_9923,
	NR_AD
}FE_AD;
// ����AEW�̣߳��ֱ��ʱ仯ʱ��Ҫ�����̣߳������¿���
// AEW�������óɺ���Ƶ����һ�¼���
// prev_share_fd������preview�豸���ļ�����ţ����Ϊ-1����aewģ���Լ������ļ����
int dahua_aew_start(AEW_WINDOW *window, int prev_share_fd);

// ������ɫ����
int dahua_aew_set_color(COLOR_PARAM *param);

// ���ð�ƽ�����
int dahua_aew_set_wb_mode(WB_MODE mode);

// ������ҹģʽ
int dahua_aew_set_dnc_mode(DNC_MODE mode);

// ������Ƶ��ʽ
// vstd:0-pal�ƣ�1-n�ƣ�2-secam��
int dahua_aew_set_vstd(VSTD vstd);

// ����A/D����
// vstd:0-pal�ƣ�1-n�ƣ�2-secam��
int dahua_aew_set_AD(FE_AD vstd);

// ��ȡ֧�ֵ��ع�ȼ���
// ����ֵ<0����ȡʧ�ܣ�>=0��ʾ�ȼ���������ȼ�����������speeds�С�
// speeds���鳤�ȱ����㹻��ȡ16����ˡ�
int dahua_aew_get_exposure_speeds(VSTD vstd, float *speeds);

// �����ع�ȼ�
// 0     �Զ��ع�
// 1~n-1 �ֶ��ع�ȼ�
// n     ��ʱ�������޵��Զ��ع�
// n+1   �Զ���ʱ���ֶ��ع�
// (n��ʾ֧�ֵ��ع�ȼ�������dahua_aew_get_exposure_speeds�ӿڷ���ֵ��
// value1:�Զ��ع�ʱ�����޻����ֶ��ع��Զ���ʱ�䣬����Ϊ��λ��ȡֵ0.1ms~80ms
// value2:�Զ��ع�ʱ�����ޣ�����Ϊ��λȡֵ0.1ms~80ms���ұ��벻С��exposureValue1ȡֵ
int dahua_aew_set_exposure_level(int level, float value1, float value2);

// ��������ֵ
// gain:�̶�����ֵ�������Զ���������ޣ�ȡֵ0-100��
// auto_gain:�Զ����棬0-��������1-������ͬʱgain��Ա��ʾ�Զ���������ޡ�
int dahua_aew_set_gain(int gain, int auto_gain);

// ���òο���ƽֵ
// level:�ο���ƽֵ��ȡֵ0-100��
int dahua_aew_set_refrence_level(int level);

// ����AEW�߳�
int dahua_aew_stop();
//���ڵ���
int dahua_aew_debug(char *cmd);

#endif
