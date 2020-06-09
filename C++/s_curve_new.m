clc;clear;close;

GoalV=500;%%��λmm/s
GoalS=1000;%%��λmm
Acc=100;
Jerk=200;
%%%%%%%%%%%%%%%%�����޸�
InitV=100;
InitS=100;
%%%%%%%%%%%%%%%%�������޸�
Vs2=InitV;
n=10;
T1=Acc/Jerk;
Vtemp=Acc^2/Jerk;%%����ٶȱ仯�������˼Ӽ��ٶȶκͼӼ��ٶȶε��ٶȱ仯

Vmax=abs(GoalV-InitV);

Vs=InitV;%%���Բ��õ����ٶȸ����ϵ������ֻҪ���Ǻ�����Ż�����λ�Ƶ���������ˡ�

J=Jerk;
%T1=sqrt((((GoalV+Vs)/2-Vs)*2)/J);

[s(1),v(1),a(1)]=SProfileT1(0,Jerk,InitV,T1);
T3=T1;
t=0;
J=-Jerk;
Vc=2*(v(1)-InitV)+InitV;

s(3)=0+(double(1)/6)*J*T3.^3-(double(1)/2)*J*T3.^2*t+(double(1)/2)*J*T3*t.^2-(double(1)/6)*J*t.^3+Vc*T3-Vc*t;

J=Jerk;

s(7)=0+(double(1)/6)*J*T3.^3-(double(1)/2)*J*T3.^2*t+(double(1)/2)*J*T3*t.^2-(double(1)/6)*J*t.^3+Vs*T3-Vs*t;%%�ⲿ��ֻ�Ǽ������T7�ε�λ�Ʊ仯��
J=-Jerk;
s(5)=0+Vc*T1+(double(1)/6)*J*T1.^3+(double(1)/2)*0*T1.^2;

S(4)=s(3)+s(5)+s(1)+s(7);%%�����Ķ�����λ�Ƶķֽ��
J=Jerk;
S(4)=4*InitV*T1+2*J*T1.^3;%%���û�ӳ�ʼ��λ�Ʊ仯��������ǰ��ļ����s(1)��s(3)��s(5)��s(7)��û�мӳ�ʼ��λ��

if Vmax<=Vtemp%%�ٶ����仯��С�ڼӼ��ٶȶκͼ����ٶȶε��ٶȱ仯������ʱ�ٶ����߷�Ϊ�Ķλ���Σ���ʱ��λ�Ƶ������ǰ��������ٶȶ��ǿ��Ը����ϵ�
    
    if S(4)<abs(GoalS-InitS) %&& InitV==Vs2  %%����������� else�����Ķ�����
        
        t1=linspace(0,T1,n);
        t=T1;
        [St{1},Vt{1},At{1}]=SProfileT1(InitS,Jerk,InitV,t1);
        
        
        t3=linspace(t,2*t,n);
        [St{3},Vt{3},At{3}]=SProfileT3(T1,-Jerk,GoalV,t3-t,S(4)/2+InitS,0);
        
        %[St{3},Vt{3},At{3}]=SProfileT32(At{1}(n),-Jerk,Vt{1}(n),t3-t,St{1}(n));
        t=2*t;
        
        T4=abs(S(4)-abs(GoalS-InitS))/GoalV;
        t4=linspace(t,t+T4,n);
        [St{4},Vt{4},At{4}]=SProfileT4(St{3}(n),GoalV,t4-t);
        t=t+T4;
        
        t5=linspace(t,t+T1,n);
        [St{5},Vt{5},At{5}]=SProfileT5(-Jerk,GoalV,t5-t,St{4}(n),At{4}(n));
        t=t+T1;
        
        t7=linspace(t,t+T1,n);
        [St{7},Vt{7},At{7}]=SProfileT7(T1,Jerk,InitV,t7-t,GoalS );
        
        %[St{7},Vt{7},At{7}]= SProfileT72(At{5}(n),J,Vt{5}(n),t7-t,St{5}(n));
        t=t+T1;
        
        
        figure('name','���λ������');
        hold on
        plot(t1,St{1});
        plot(t3,St{3});
        plot(t4,St{4});
        plot(t5,St{5},'y');
        plot(t7,St{7},'b');
        figure('name','����ٶ�����');
        hold on
        plot(t1,Vt{1});
        plot(t3,Vt{3});
        plot(t4,Vt{4},'r');
        plot(t5,Vt{5},'y');
        plot(t7,Vt{7},'b');
        
        figure('name','��μ��ٶ�����');
        hold on
        plot(t1,At{1});
        plot(t3,At{3});
        plot(t4,At{4});
        plot(t5,At{5},'y');
        plot(t7,At{7},'b');
    elseif S(4)>=abs(GoalS-InitS)
        
        sc=abs(GoalS-InitS);
        J=Jerk;
        fun=@(T)(sc-4*InitV*T-2*J*T.^3);
        T=fsolve(fun,0.1);
        
        Vs=InitV;
        J=Jerk;
        
        t1=linspace(0,T,n);
        t=T;
        [St{1},Vt{1},At{1}]=SProfileT1(InitS,Jerk,Vs,t1);
        
        
        J=-Jerk;
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        sm=0
        vm=Vt{1}(n);
        am=At{1}(n);
        
        t3=linspace(t,t+T,n);
        [St{3},Vt{3},At{3}]=SProfileT32(am,J,vm,t3-t,St{1}(n));
        t=T+T;
        
        
        J=-Jerk;
        Vc=Vt{3}(n);
        a4=At{3}(n);
        s4=St{3}(n);
        
        t5=linspace(t,t+T,n);
        [St{5},Vt{5},At{5}]=SProfileT5(J,Vc,t5-t,s4,a4);
        t=t+T;
        
        J=Jerk;
        
        t7=linspace(t,t+T,n);
        [St{7},Vt{7},At{7}]= SProfileT72(At{5}(n),J,Vt{5}(n),t7-t,St{5}(n));
        t=t+T;
        figure('name','�Ķ�λ������');
        hold on
        plot(t1,St{1});
        plot(t3,St{3});
        plot(t5,St{5},'y');
        plot(t7,St{7},'b');
        figure('name','�Ķ��ٶ�����');
        hold on
        plot(t1,Vt{1});
        plot(t3,Vt{3});
        plot(t5,Vt{5},'y');
        plot(t7,Vt{7},'b');
        
        figure('name','�Ķμ��ٶ�����');
        hold on
        plot(t1,At{1});
        plot(t3,At{3});
        plot(t5,At{5},'y');
        plot(t7,At{7},'b');
    end
else
    if S(4)<abs(GoalS-InitS) %%�ɷ�Ϊ���κ��߶δ����Ķε�λ������
        %%�ȼ������ε�λ�����������õ�ʱ��������һ��
        t=T1;
        J=Jerk;
        s(1)=0+(double(1)/6)*J*t.^3+Vs*t;
        [s(1),v(1),a(1)]=SProfileT1(0,J,InitV,T1);
        [s(2),v(2),a(2)]=SProfileT2(T1,J,v(1),T1,0);
        J=-Jerk;
        [s(3),v(3),a(3)]=SProfileT32(a(2),J,v(2),T1,0);
        [s(5),v(5),a(5)]=SProfileT5(J,v(3),T1,0,0);
        [s(6),v(6),a(6)]=SProfileT6( T1,J,v(5),T1,0);
        J=Jerk;
        [s(7),v(7),a(7)]=SProfileT72(a(6),J,v(6),T1,0);
        S(6)=s(1)+s(2)+s(3)+s(5)+s(6)+s(7);
        if S(6)<=abs(GoalS-InitS)%%�������ε�ʱ���λ��
            
            J=Jerk;
            t1=linspace(0,T1,n);
            [St{1},Vt{1},At{1}]=SProfileT1(InitS,J,InitV,t1);
            t=T1;
            
            t2=linspace(t,t+T1,n);
            [St{2},Vt{2},At{2}]=SProfileT2(T1,J,Vt{1}(n),t2-t,St{1}(n));
            t=t+T1;
            
            J=-Jerk;
            t3=linspace(t,t+T1,n);
            [St{3},Vt{3},At{3}]=SProfileT32(At{2}(n),J,Vt{2}(n),t3-t,St{2}(n));
            t=t+T1;
            
            T4=abs(S(6)-abs(GoalS-InitS))/Vt{3}(n);
            t4=linspace(t,t+T4,n);
            [St{4},Vt{4},At{4}]=SProfileT4(St{3}(n),Vt{3}(n),t4-t);
            t=t+T4;
            
            
            t5=linspace(t,t+T1,n);
            [St{5},Vt{5},At{5}]=SProfileT5(J,Vt{4}(n),t5-t,St{4}(n),0);
            t=t+T1;
            
            t6=linspace(t,t+T1,n);
            [St{6},Vt{6},At{6}]=SProfileT6( T1,J,Vt{5}(n),t6-t,St{5}(n));
            t=t+T1;
            
            t7=linspace(t,t+T1,n);
            J=Jerk;
            [St{7},Vt{7},At{7}]=SProfileT72(At{6}(n),J,Vt{6}(n),t7-t,St{6}(n));
            
            t=t+T1;
            figure('name','�߶�λ������');
            hold on
            plot(t1,St{1});
            plot(t2,St{2});
            plot(t3,St{3});
            plot(t4,St{4});
            plot(t5,St{5},'y');
            plot(t6,St{6},'r');
            plot(t7,St{7},'b');
            figure('name','�߶��ٶ�����');
            hold on
            plot(t1,Vt{1});
            plot(t2,Vt{2});
            plot(t3,Vt{3});
            plot(t4,Vt{4});
            plot(t5,Vt{5},'y');
            plot(t6,Vt{6},'r');
            plot(t7,Vt{7},'b');
            
            figure('name','�߶μ��ٶ�����');
            hold on
            plot(t1,At{1});
            plot(t2,At{2});
            plot(t3,At{3});
            plot(t4,At{4});
            plot(t5,At{5},'y');
            plot(t6,At{6});
            plot(t7,At{7},'b');
        else
            
            st=abs(GoalS-InitS)/2;
            
            T1=Acc/Jerk;
            J=Jerk;
            t1=linspace(0,T1,n);
            [St{1},Vt{1},At{1}]=SProfileT1(InitS,J,InitV,t1);
            t=T1;
            
            
            
            fun=@(tp)(-st+(double(1)/6)*J*T1.^3+InitV*T1+0+Vt{1}(n)*tp+(double(1)/2)*J*T1*tp.^2+(double(1)/6)*(-1*J)*T1.^3+(double(1)/2)*(J*T1+0*tp)*T1.^2+(Vt{1}(n)+J*T1*tp)*T1);
            T2=fsolve(fun,0.1);
            
            
            t2=linspace(t,t+T2,n);
            [St{2},Vt{2},At{2}]=SProfileT2(T1,J,Vt{1}(n),t2-t,St{1}(n));
            t=t+T2;
            
            J=-Jerk;
            t3=linspace(t,t+T1,n);
            [St{3},Vt{3},At{3}]=SProfileT32(At{2}(n),J,Vt{2}(n),t3-t,St{2}(n));
            t=t+T1;
            
            t5=linspace(t,t+T1,n);
            [St{5},Vt{5},At{5}]=SProfileT5(J,Vt{3}(n),t5-t,St{3}(n),0);
            t=t+T1;
            
            t6=linspace(t,t+T2,n);
            [St{6},Vt{6},At{6}]=SProfileT6( T1,J,Vt{5}(n),t6-t,St{5}(n));
            t=t+T2;
            
            t7=linspace(t,t+T1,n);
            J=Jerk;
            [St{7},Vt{7},At{7}]=SProfileT72(At{6}(n),J,Vt{6}(n),t7-t,St{6}(n));
            
            t=t+T1;
            
            figure('name','����λ������');
            hold on
            plot(t1,St{1});
            plot(t2,St{2});
            plot(t3,St{3});
            
            plot(t5,St{5},'y');
            plot(t6,St{6},'r');
            plot(t7,St{7},'b');
            figure('name','�����ٶ�����');
            hold on
            plot(t1,Vt{1});
            plot(t2,Vt{2});
            plot(t3,Vt{3});
            
            plot(t5,Vt{5},'y');
            plot(t6,Vt{6},'r');
            plot(t7,Vt{7},'b');
            
            figure('name','���μ��ٶ�����');
            hold on
            plot(t1,At{1});
            plot(t2,At{2});
            plot(t3,At{3});
            
            plot(t5,At{5},'y');
            plot(t6,At{6});
            plot(t7,At{7},'b');
        end
    else
        %%%%%%%%%%%%%%%%%%%%�Ķ�����
        sc=abs(GoalS-InitS);
        J=Jerk;
        fun=@(T)(sc-4*InitV*T-2*J*T.^3);
        T=fsolve(fun,0.1);
        
        Vs=InitV;
        J=Jerk;
        
        t1=linspace(0,T,n);
        t=T;
        [St{1},Vt{1},At{1}]=SProfileT1(InitS,Jerk,Vs,t1);
        
        
        J=-Jerk;
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        sm=0
        vm=Vt{1}(n);
        am=At{1}(n);
        
        t3=linspace(t,t+T,n);
        [St{3},Vt{3},At{3}]=SProfileT32(am,J,vm,t3-t,St{1}(n));
        t=T+T;
        
        
        J=-Jerk;
        Vc=Vt{3}(n);
        a4=At{3}(n);
        s4=St{3}(n);
        
        t5=linspace(t,t+T,n);
        [St{5},Vt{5},At{5}]=SProfileT5(J,Vc,t5-t,s4,a4);
        t=t+T;
        
        J=Jerk;
        
        t7=linspace(t,t+T,n);
        [St{7},Vt{7},At{7}]= SProfileT72(At{5}(n),J,Vt{5}(n),t7-t,St{5}(n));
        t=t+T;
        figure('name','�Ķ�λ������');
        hold on
        plot(t1,St{1});
        plot(t3,St{3});
        plot(t5,St{5},'y');
        plot(t7,St{7},'b');
        figure('name','�Ķ��ٶ�����');
        hold on
        plot(t1,Vt{1});
        plot(t3,Vt{3});
        plot(t5,Vt{5},'y');
        plot(t7,Vt{7},'b');
        
        figure('name','�Ķμ��ٶ�����');
        hold on
        plot(t1,At{1});
        plot(t3,At{3});
        plot(t5,At{5},'y');
        plot(t7,At{7},'b');
    end
end

% S1������
function [ s,v,a ] = SProfileT1(S0,J,Vs,t)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
s=S0+(double(1)/6)*J*t.^3+Vs*t;
v=(double(1)/2)*J*t.^2+Vs;
a=J*t;
end

% S2������
function [ s,v,a] = SProfileT2(T1,J,Vl,t,S0)%%��עһ�������T2ʱ��������T1ʱ��
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
s=S0+Vl*t+(double(1)/2)*J*T1*t.^2;
v=Vl+J*T1*t;
a=J*T1+0*t;
end

% S3������ĩ���ٶȵ�����
function [ s,v,a] = SProfileT3( T3,J,Vc,t,St3,a3)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
v=Vc+(double(1)/2)*J*(T3-t).^2-a3*(T3-t);%%��Ϊ���ڸ���ʱ��ȥ���ٶ�Vm�����ٶ�V2���ٶ�����ǰ�����ʱ�����ģ������԰�It�ļ������ʱʱ����ܳ�����T3����It
s=St3-(double(1)/6)*J*(T3-t).^3+(double(1)/2)*a3*(T3-t).^2-Vc*(T3-t);
a=a3-J*(T3-t);
end

% S3������ĩ���ٶ�������
function [ s,v,a ] = SProfileT32( am,J,vm,t,sm)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
a=am+J*t;
v=vm+am*t+(double(1)/2)*J*t.^2;
s=sm+(double(1)/6)*J*t.^3+(double(1)/2)*am*t.^2+vm*t;
end

% S4������
function [ s,v,a ] = SProfileT4(S0,Vc,t)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
a=t*0;
v=Vc+0*t;
s=Vc*t+S0;
end

% S5������
function [ s,v,a ] = SProfileT5(J,Vc,t,s4,a4)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
v=Vc+(double(1)/2)*J*t.^2+a4*t;
s=s4+Vc*t+(double(1)/6)*J*t.^3+(double(1)/2)*a4*t.^2;
a=a4+J*t;
end

% S6������
function [ s,v,a] = SProfileT6( T5,J,Vm2,t,S5)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
v=Vm2+J*T5*t;
s=S5+Vm2*t+(double(1)/2)*J*T5*t.^2;
a=J*T5+0*t;
end

% S7�����ߵ�����
function [ s,v,a] = SProfileT7( T7,J,Vs2,t,St7 )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
v=Vs2+(double(1)/2)*J*(T7-t).^2;
s=St7-(double(1)/6)*J*T7.^3+(double(1)/2)*J*T7.^2*t-(double(1)/2)*J*T7*t.^2+(double(1)/6)*J*t.^3-Vs2*T7+Vs2*t;
a=-J*(T7-t);
end

% S7������������
function [ s,v,a ] = SProfileT72( al2,J,vl2,t,sl2)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
a=al2+J*t;
v=vl2+al2*t+(double(1)/2)*J*t.^2;
s=sl2+(double(1)/6)*J*t.^3+(double(1)/2)*al2*t.^2+vl2*t;
end
