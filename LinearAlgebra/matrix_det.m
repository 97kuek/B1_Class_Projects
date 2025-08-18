%% 行列の行列式を求めるプログラム

clear; clc;

% 行列を入力
A = input('行列Aを入力: ');

% 正方行列か確認
[ra, ca] = size(A);

if ra ~= ca
    error('行列式は正方行列にのみ定義されます');
end

% 行列式を計算
d = det(A);

% 行列式を出力
disp('行列Aのdet = ');
disp(d);