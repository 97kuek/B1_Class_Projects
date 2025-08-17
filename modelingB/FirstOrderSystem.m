%% 一次遅れ系のシミュレーション(ステップ入力応答と正弦波入力応答)

clear; clc; close all;

%% パラメータ
K   = 1.0;          % ゲイン（系のゲイン）
tau = 2.0;          % 時定数 [s]
y0  = 0.0;          % 初期値 y(0)
omega = 0.5;        % 正弦波入力の角周波数 [rad/s]
A = 2.0;            % 正弦波入力の振幅

% ODE右辺
f = @(t,y,u) (-y + K*u(t)) / tau;

% ODEソルバの精度設定
opts = odeset('RelTol',1e-8,'AbsTol',1e-10);

%% 1) ステップ応答
u_step = @(t) (t>=0);                                       % 単位ステップ入力
tspan1  = [-5 20];                                          % シミュレーション時間
[t1, y1] = ode45(@(t,y) f(t,y,u_step), tspan1, y0, opts);

%% 2) 正弦波入力応答
u_sin = @(t) A*sin(omega*t);                                % 振幅A,角周波数omegaの正弦波入力
tspan2 = [-5 40];                                           % シミュレーション時間
[t2, y2] = ode45(@(t,y) f(t,y,u_sin), tspan2, y0, opts);
M = K / sqrt(1 + (omega*tau)^2);                            % 振幅比
phi = -atan(omega*tau);                                     % 位相のずれ
A_out = A * M;                                              % 出力振幅

%% 3) グラフ描画
figure;

% ステップ応答
subplot(2,1,1);                                             % 画面を2行1列に分割し1番目にプロットを書く
plot(t1, u_step(t1), 'r--', 'LineWidth', 1.2); hold on;     % 入力
plot(t1, y1, 'b-', 'LineWidth', 2);                         % 出力
grid on; box on;
title('一次遅れ系：ステップ応答');
xlabel('Time [s]'); ylabel('Amplitude');
legend('入力 u(t)', '出力 y(t)');

% 正弦波応答
subplot(2,1,2);
plot(t2, u_sin(t2), 'r--', 'LineWidth', 1.2); hold on;
plot(t2, y2, 'b-', 'LineWidth', 2);
grid on; box on;
title('一次遅れ系：正弦波入力応答');
xlabel('Time [s]'); ylabel('Amplitude');
legend('入力 u(t)', '出力 y(t)');
txt = {
    sprintf('入力振幅 A = %.2f', A)
    sprintf('出力振幅 A_{out} ≈ %.3f', A_out)
    sprintf('振幅比　M = %.3f', M)
    sprintf('位相のずれ φ = %.2f deg', rad2deg(phi))
};
text(-4, 0.8*A, txt, 'FontSize', 9, 'BackgroundColor','w');
