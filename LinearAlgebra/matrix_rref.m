%% 行列の簡約化,rankを求めるプログラム

clear; clc;

% 入力
A = input('行列Aを入力: ');
tol_in = input('許容誤差 tol（Enterで既定=1e-12）： ','s');
if isempty(tol_in)
    tol = 1e-12;
else
    tol = str2double(tol_in);
    if isnan(tol) || tol <= 0
        warning('不正な tol なので既定値 1e-12 を使用します。');
        tol = 1e-12;
    end
end
if ~ismatrix(A)
    error('行列を入力してください');
end

% 実行
[R, rankA] = rref_with_steps(A,tol); % ローカル関数参照

% 結果表示
disp('==============================');
disp('最終的な行簡約形 (RREF):');
disp(R);
fprintf('rank(A) = %d\n', rankA);

% 検算（MATLAB組込みと比較）
[RR_builtin, ~] = rref(A, tol);
if norm(R - RR_builtin, 'fro') < 1e-9 * max(1, norm(RR_builtin,'fro'))
    disp('（検算）MATLAB組込み rref と一致しています。');
else
    disp('（検算）MATLAB組込み rref と完全には一致しません（丸めや許容値の影響かもしれません）。');
end

% ローカル関数
function [R, rankA] = rref_with_steps(A, tol)
    [m, n] = size(A);
    R = A;
    row = 1;                                                % これから処理する行のindex 最初は1行目
    fprintf('初期行列 A:\n'); disp(R);

    % 1列ごとに処理を進める
    for col = 1:n
        if row > m, break; end % 行が全て終わったなら終了

        % --- ピボット（最大絶対値）探索：行 row..m, 列 col ---
        [pivot_val, pivot_rel] = max(abs(R(row:m, col)));
        pivot_row = row + pivot_rel - 1;

        if pivot_val <= tol
            % この列は実質ゼロ列 → 次の列へ
            continue;
        end

        % --- 行の入れ替え（必要なら） ---
        if pivot_row ~= row
            R([row, pivot_row], :) = R([pivot_row, row], :);
            printStep(sprintf('R_%d <-> R_%d（行の入れ替え：ピボットを上へ）', row, pivot_row), R);
        end

        % --- ピボット行の正規化（ピボットを1に） ---
        pivot = R(row, col);
        if abs(pivot) > tol && abs(pivot - 1) > tol
            R(row, :) = R(row, :) / pivot;
            printStep(sprintf('R_%d := R_%d / (%.12g)（ピボットを1に正規化）', row, row, pivot), R);
        end

        % --- ピボット列の他行を 0 に（前進+後退を一気に：ガウス・ジョルダン） ---
        for r = 1:m
            if r == row, continue; end
            factor = R(r, col);
            if abs(factor) > tol
                R(r, :) = R(r, :) - factor * R(row, :);
                printStep(sprintf('R_%d := R_%d - (%.12g)*R_%d（ピボット列の掃き出し）', ...
                                   r, r, factor, row), R);
            end
        end

        % 次のピボット行へ
        row = row + 1;
    end

    % --- 数値ノイズの丸め ---
    R(abs(R) < tol) = 0;

    % --- rank の算出（非ゼロ行の数） ---
    nz = any(abs(R) > 0, 2);     % 要素が1つでも非ゼロなら非ゼロ行
    rankA = sum(nz);
end

function printStep(msg, M)
    % 1ステップの説明と行列を見やすく表示
    fprintf('--- %s ---\n', msg);
    disp(M);
end