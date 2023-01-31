#include "U51V2.h"

unsigned char State            = 0; // �����ʱ����������
unsigned char Trans            = 0; // ����ѡ��ť
unsigned char Countdown        = 0; // �Ƿ�������ʱ
unsigned char BUFF_State       = 0;
unsigned char Countdown_minite = 0, Countdown_second = 0; // ����ʱ
unsigned int Countdown_msecond = 0;
unsigned int count             = 0;             // ����Ƿ�ʼ������F_Countdown_msΪ��־λ
unsigned char Ms_clock = 0, F_Countdown_ms = 0; // ���ر�״̬
unsigned char hour, minute, second;
unsigned char Clock = 0, Clock_hour = 0, Clock_minite = 0, ring = 0; // ʵ�����ӹ���,Ĭ���ǹر�״̬
unsigned char Set_hour = 0, Set_minite = 0, Set_second = 0;          // ����ʱ����
unsigned char year = 22, month = 1, day = 1;
unsigned int ms;
unsigned char LED_buf[8]  = {17, 0, 16, 0, 0, 16, 0, 0};
unsigned char M_Day[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/*******��ʾLED**********/
void display()
{
    unsigned char i;
    for (i = 0; i < 8; i++) {
        display_LED_idx(LED_buf[i], i);
        delay_ms(1);
    }
    display_LED_idx(17, 7);
     //������Ӱ
}
/*******������������******/
void Fix_Year_Month() // ������������
{
    if (((2000 + year) % 4 == 0) && (2000 + year) % 400 != 0)
        M_Day[1] = 29;
    else
        M_Day[1] = 28;
}
/**********װ��LED����***********/
void load_LED(unsigned char first, unsigned char second, unsigned char third, unsigned char mod)
{
    LED_buf[0] = first / 10;
    if (mod == 1)
        LED_buf[0] = 17;
    LED_buf[1] = first % 10;
    LED_buf[3] = second / 10;
    LED_buf[4] = second % 10;
    LED_buf[6] = third / 10;
    LED_buf[7] = third % 10;
}
/*********��ȡ���µİ���**********/
unsigned int code key_val[4] = {425, 444, 488, 609};
unsigned char get_k()
{
    unsigned int AD_val;
    char k = 0;
    AD_val = get_AD(3); // 408/425/448/488/609
    for (k = 1; k < 5; k++) {
        if (AD_val > key_val[k - 1] - 4 - k && AD_val < key_val[k - 1] + 4 + k)
            break;
    }
    if (k == 5) k = 0;
    return k;
}
/****************����������*********************/
void Buff(unsigned char j)
{
    for (j = 0; j < 5; j++) {
        P34 = 1;
        delay_ms(20);
        P34 = 0;
        delay_ms(20);
    }
}
/***********��ȡģ�ⰴ��ֵ*************/
void key()
{
    char k;
    k = get_k();
    if (k > 0) {
        display();
        if (k == get_k()) {
            if (Trans == 1) {
                switch (k) {
                    case 1:
                        if (hour > 0) hour--;
                        break;
                    case 2:
                        if (hour < 24) hour++;
                        break;
                    case 3:
                        if (minute > 0) minute--;
                        break;
                    case 4:
                        if (minute < 59) minute++;
                        break;
                    default:

                        break;
                }
            } else if (Trans == 0) {
                switch (k) {
                    Fix_Year_Month(); // ��������
                    case 1:
                        if (year > 20) year--;
                        break;
                    case 2:
                        if (year < 99) year++;
                        break;
                    case 3:
                        if (month > 0) month++;
                        if (month > 12) month = month % 12;
                        break;
                    case 4:
                        if (day <= M_Day[month - 1]) day++;
                        if (day > M_Day[month - 1]) day = day % M_Day[month - 1];
                        break;
                    default:
                        break;
                }
            } else if (Trans == 2) {
                switch (k) {
                    case 1: {
                        Set_second = 0;
                        Set_hour += 1;
                        if (Set_hour >= 24)
                            Set_hour %= 24;
                    } break;
                    case 2: {
                        Set_second = 0;
                        if (Set_minite < 59)
                            Set_minite += 1;
                    } break;
                    case 3: {
                        Set_second = 0;
                        if (Set_minite > 0)
                            Set_minite -= 1;
                    } break;
                    case 4: {
                        if (Countdown == 0)
                            Countdown = 1; // ��������ֹͣ����ʱ
                        else
                            Countdown = 0;
                    } break;
                    default:
                        break;
                }
            } else if (Trans == 3) {
                switch (k) {
                    case 1: {
                        Clock_hour += 1;
                        if (Clock_hour >= 24)
                            Clock_hour %= 24;
                    } break;
                    case 2: {
                        if (Clock_minite < 59)
                            Clock_minite += 1;
                    } break;
                    case 3: {
                        if (Clock_minite > 0)
                            Clock_minite -= 1;
                    } break;
                    case 4: {
                        if (Clock == 0)
                            Clock = 1; // ��������ֹͣ����ʱ
                        else
                            Clock = 0;
                    } break;
                    default:
                        break;
                }
            } else if (Trans == 4) {
                if (k == 4) // �Ƿ�ʼ���״̬
                {
                    if (count == 0)
                        count = 1;
                    else
                        count = 0;
                    Ms_clock = count; // ȷ���������״̬
                }
            }
        }
        while (k > 0) {
            k = get_k();    // ֻ���޸�ʱ��ʱ�������Ż�����
            if (Trans == 1) //
            {
                second = 0;
                load_LED(hour, minute, second, 0); // ��ʾʱ��
            } else if (Trans == 0)
                load_LED(year, month, day, 0); // ��ʾ����
            else if (Trans == 2)
                load_LED(Set_hour, Set_minite, Set_second, 1);
            else if (Trans == 3)
                load_LED(Clock_hour, Clock_minite, 0, 0);
            else
                load_LED(Countdown_minite, Countdown_second, Countdown_msecond / 10, 0);
            display();
        }
    }
}
void main()
{
    P2 = 0x00;
    init_AD(3);
    init_T_us_P(int_T0, 1000, 0);
    init_INT_M_P(int_I1, 1, 0);
    T0_Run();
    EA_On();
    LED_On();
    while (1) {
        P2 = 0x01 << Trans; // �е�����
        key();
        if (Trans == 1)
            load_LED(hour, minute, second, 0); // ���
        else if (Trans == 0)
            load_LED(year, month, day, 0);
        else if (Trans == 2) // ����ʱ
            load_LED(Set_hour, Set_minite, Set_second, 0);
        else if (Trans == 3) // ����
            load_LED(Clock_hour, Clock_minite, 0, 0);
        else // ���
            load_LED(Countdown_minite, Countdown_second, Countdown_msecond / 10, 0);
        if (BUFF_State) {
            Buff(5);
            BUFF_State = 0;
        }
        // P25=Countdown
        ; // ָʾ����
        // P26=Clock;
        // P27=count;
        display();
    }
}

void ISR_I1() interrupt int_I1
{
    if (P33 == 0) {
        delay_ms(5);
        if (P33 == 0) {
            Trans += 1;
            Trans = Trans % 5;
        }
    }
    while (P33 == 0) {
        delay_ms(5);
    }
}
void ISR_T0() interrupt int_T0
{
    if (++ms >= 1000) {
        ms = 0;
        // ��ʾ���ں�ʱ��
        if (++second >= 60) {
            second = 0;
            if (++minute >= 60) {
                minute = 0;
                if (++hour >= 24) {
                    hour  = 0;
                    State = 1;
                }
            }
        }
        // ����ʱ
        if (Countdown == 1) {
            if (Set_second-- == 0) {
                if (Set_minite == 0 && Set_hour == 0) {
                    Set_second = 0;
                    Countdown  = 0; // ����ʱ����
                    BUFF_State = 1;
                } else {
                    Set_second = 59;
                    if (Set_minite-- == 0) {
                        Set_minite = 59;
                        Set_hour -= 1;
                    }
                }
            }
        }
    }
    if (State == 1) {
        State = 0;
        day += 1;
        if (day > M_Day[month - 1]) {
            day = 0;
            month += 1;
            if (month > 12) {
                month = 0;
                year += 1;
                if (year > 99)
                    year = 22;
            }
        }
    }
    if (Clock == 1) // ��ʱ������
    {
        if (hour == Clock_hour && minute == Clock_minite) {
            BUFF_State = 1;
            Clock      = 0;
        }
    }
    if (count == 1) // �������״̬
    {
        if (Ms_clock == 1) {
            F_Countdown_ms   = ms; // ȡ��һ�������
            Countdown_second = 0;
            Countdown_minite = 0;
            Ms_clock         = 0;
        }
        if (F_Countdown_ms <= ms && ms <= 999) {
            Countdown_msecond = ms - F_Countdown_ms;
        } else // �����һ����ʼ״̬
        {
            Countdown_msecond = ms + 1000 - F_Countdown_ms;
        }
        if (Countdown_msecond >= 999) {
            Countdown_second += 1;
            if (Countdown_second >= 60) {
                Countdown_second = 0;
                Countdown_minite += 1;
                if (Countdown_minite >= 60) {
                    Countdown_minite = 0;
                }
            }
        }
    }
}