%% 行列の積を求めるプログラム

clear; clc;

% 行列Aと行列Bを入力
A = input('行列Aを入力: ');
B = input('行列Bを入力: ');

% 行列のサイズ確認
[ra, ca] = size(A);
[rb, cb] = size(B);

if ca ~= rb % ~は否定を表す
    error('行列の積は計算できません。Aの列数とBの行数が一致していません。');
end

% 行列の積を計算
C = A * B;

% 結果を表示
disp('行列A × 行列B の結果は:');
disp(C);
