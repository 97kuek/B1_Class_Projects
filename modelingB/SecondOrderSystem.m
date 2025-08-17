%% 二次遅れ系のステップ応答シミュレーション

clear; clc; close all;

%% パラメータ設定
K     = 1.0;     % ゲイン
tau   = 2.0;     % 時定数 [s]
zeta  = 0.1;     % 減衰係数 (0<zeta<1: 振動, zeta=1: 臨界, zeta>1: 過減衰)

% 初期条件
y0    = 0.0;     % y(0)
dy0   = 0.0;     % y'(0)

%% ODE定義
f = @(t,x,u) [ ...
    x(2); 
    (-2*zeta*tau*x(2) - x(1) + K*u(t)) / (tau^2) ...
];

%% ステップ入力
u_step  = @(t) (t>=0);   % 単位ステップ
tspan   = [-5 40];       % シミュレーション時間
x0      = [y0; dy0];     % 初期条件ベクトル

%% 数値解
opts = odeset('RelTol',1e-8,'AbsTol',1e-10);
[t, x] = ode45(@(t,x) f(t,x,u_step), tspan, x0, opts);
y = x(:,1);

%% グラフ描画
figure('Name','二次遅れ系 ステップ応答','Color','w');
plot(t, u_step(t), 'r--', 'LineWidth', 1.2); hold on;
plot(t, y, 'b-', 'LineWidth', 2);
grid on; box on;
title(sprintf('二次遅れ系：ステップ応答 (K=%.1f, \\tau=%.1f, \\zeta=%.2f)', K, tau, zeta));
xlabel('Time [s]');
ylabel('Amplitude');
txt = {
    sprintf('ゲイン K = %.1f', K)
    sprintf('時定数 \\tau = %.1f', tau)
    sprintf('減衰係数 \\zeta = %.2f', zeta)
};
text(30, 0.2*K, txt, 'FontSize', 9, 'BackgroundColor','w');