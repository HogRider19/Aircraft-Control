clear all; clc;
close all;

h=0.001;
Df=2;
a=5;
c=2000;
n=12000;

S0=h/12;
k=(2*Df/a/S0)^(1/2);
E=rand(1,n);
T=1/a;
X(1)=0;
for i=1:n-1
    X(i+1)=(-1/T*X(i)+k/T*E(i))*h+X(i);
end
mx=0;
for i=0:n-1-c
    mx=mx+X(c+i+1);
end
mx=mx/(n-c);
tt(1)=0;
t=0:h:T;
% K(1)=Df;
for i=1:n-1
    % K(i+1)=Df*exp(-a*t(i));
    tt(i+1)=3/a/n*i;
end

for i=1:n-c
    sum=0;
    for j=1:n-c-i+1
        sum=sum+(X(c+j)-mx)*(X(c+j+i-1)-mx);
    end
    Kx(i)=sum/(n-c-i-1);
    % tau(i)=3/a/(n-c)*i;
end

figure
plot(t,Df*exp(-a*t),t,Kx(1:T/h+1));
grid on;
title('Корреляционная функция');
legend('Теоретическая','Полученная')
xlabel('Время, с');

% figure
% plot(t,Kx(1:T/h+1));
% grid on;
% title('Корреляционная функция после применения формирующего фильтра');
% xlabel('Время, с');

figure
plot(tt,X);
grid on;
title('Случайный процесс после формирующего фильтра')
xlabel('Время, с');