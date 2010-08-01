//
//  "$Id: ae.c 513 2010-04-26 01:21:14Z wang_jun $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:	
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "aew.h"

int ae_process( AEW_PAXEL_STAT *stat, AEW_PAXEL_INFO *info, int refrence_level, EXPLORE_PARAM *param)
{
	static int y_max = 255;			// ������ֵ
	static int exp_level = 128;		// ��ǰ�ع�ȼ�
	static int exp_level_max = 255;	// ����ع�ȼ�
	static int exp_level_min = 0;	// ��С�ع�ȼ�
	static int ev_default = 72;		// Ĭ��������ƽ����ƽ
	static int ev_diff_max = 8;
	int hist[256];					// ����ֱ��ͼͳ��
	
	int ev = 0;
	int mid = 0;
	int i, n = 0;
	float gain_extra = 1.0;
	
	memset(hist, 0, sizeof(hist));
	
	// ����ֱ��ͼ
	for(i = info->hz_cnt; i < info->vt_cnt * info->hz_cnt; i++)
	{
		hist[stat[i].y]++;
	}
	/*jerry n < (info->vt_cnt - 1) * info->hz_cnt / 2 ��������Ǹ�ʲô*/
	for(mid = 255, n = 0; mid >=0 && n < (info->vt_cnt - 1) * info->hz_cnt / 2; mid--)
	{
		n += hist[mid]; /*ֱ��ͼ�Ѿ�����������,��������ֻҪͳ�ƾ�OK��*/
	}
	
	ev = 0;
	n = 0;
	
	// ֻͳ�Ʋ�С����ֵ���Ҳ��Ǹ������������
	for(i = info->hz_cnt; i < info->vt_cnt * info->hz_cnt; i++)
	{
		if(stat[i].y >= mid && stat[i].y <= y_max)
		{
			ev += stat[i].y;
			n++;
		}
	}
	
	if(n)
	{
		ev /= n;
	}
	else
	{
		ev = mid;
	}
	
	int ev_avg = ev_default;
	
	// ��0-50-100ӳ��Ϊ0-ev_default-255
	if(refrence_level < 50)
	{
		ev_avg = refrence_level * ev_default / 50;
	}
	else
	{
		ev_avg = (ev_default + (refrence_level - 50) * (255 - ev_default) / 50);
	}
	
	int delta = abs(ev - ev_avg);
	if(delta > ev_diff_max)
	{
		int step = sqrt(delta);
		if(ev > ev_avg)
		{
			exp_level -= step;	
		}
		else
		{
			exp_level += step;
		}
		if(exp_level > exp_level_max)
		{
			exp_level = exp_level_max;
			//gain_extra = (float)ev_avg / (ev ? ev : 1);
		}
		else if(exp_level < exp_level_min)
		{
			exp_level = exp_level_min;
			gain_extra = (float)ev_avg / (ev ? ev : 1);
		}
	}
	
	param->ev = ev;
	param->level = exp_level;
	param->gain_extra = gain_extra;
	
	//printf("ev = %d, level = %d, extra = %f\n", ev, exp_level, gain_extra);
	
	return 0;
}
