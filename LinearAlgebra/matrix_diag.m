%% 行列の対角化（固有値は実数のみを想定）+ 診断付き
%  - A が正方行列かチェック
%  - 固有値が実数かチェック（複素固有値が含まれる場合は中断）
%  - V の列ベクトルが一次独立（rank(V)=n）なら対角化可能
%  - 各固有値の代数的重複度/幾何学的重複度を表示
%  - A が実対称なら直交対角化（P'P=I）も検証
%
% 使い方の例：
%   A = [4 1 0; 1 4 0; 0 0 2];  % 実対称 → 直交対角化可
%   A = [5 4 2; 0 1 0; 0 0 1];  % 重根あり、対角化できない例（幾何学的重複度が不足）
%
clear; clc;

% 入力
A = input('行列Aを入力： ');
tol_in = input('許容誤差 tol（Enterで既定=1e-10）: ','s');
if isempty(tol_in)
    tol = 1e-10;
else
    tol = str2double(tol_in);
    if isnan(tol) || tol <= 0
        warning('不正な tol なので既定値 1e-10 を使用します。');
        tol = 1e-10;
    end
end

% 実行
[P, D, info] = diagonalize_with_steps(A, tol);

% ---- 出力 ----
if ~info.is_square
    error('A は正方行列ではありません。');
end

if ~info.real_eigs
    error('固有値に虚部を含みます。このプログラムは「実数固有値のみ」を想定しています。');
end

if info.is_diagonalizable
    disp('==============================');
    disp('対角化に成功しました（A = P * D / P）:');
    disp('P ='); disp(P);
    disp('D ='); disp(D);
    fprintf('検算 ||A - P*D/P||_F = %.3e\n', info.residual);
    if info.is_symmetric
        fprintf('A は実対称です。P は直交（P''*P ≈ I）。||P''P - I||_F = %.3e\n', info.orth_residual);
    end
else
    disp('==============================');
    disp('対角化できません（V=固有ベクトル行列の列が一次独立でない）:');
    fprintf('rank(V) = %d / n=%d\n', info.rankV, info.n);
    disp('--- 固有値ごとの重複度 ---');
    T = table(info.lambda(:), info.alg_mult(:), info.geom_mult(:), ...
              'VariableNames', {'lambda','alg_mult','geom_mult'});
    disp(T);
    if info.is_symmetric
        disp('※ ただし A は実対称のはずなので、本来は直交対角化可能です。tol を見直してください。');
    end
end

%% ====== ローカル関数 ======
function [P, D, info] = diagonalize_with_steps(A, tol)
    % 初期化
    P = []; D = [];
    [m, n] = size(A);
    info = struct();
    info.is_square = (m == n);
    info.n = n;
    if ~info.is_square
        return;
    end

    % 実対称かどうか（数値誤差考慮）
    info.is_symmetric = norm(A - A.', 'fro') <= tol;

    % 固有分解
    [V, Dfull] = eig(A);    % A*V = V*Dfull
    lam = diag(Dfull);
    % 固有値が実数か確認
    if any(abs(imag(lam)) > tol)
        info.real_eigs = false;
        return;
    else
        info.real_eigs = true;
        lam = real(lam);
        V   = real(V);
        Dfull = diag(lam);
    end

    % 診断：対角化可能性（rank(V)=n ?）
    info.rankV = rank(V, tol);
    info.is_diagonalizable = (info.rankV == n);

    % 固有値ごとの代数的重複度・幾何学的重複度を算出（学習向け表示）
    [uniq_lambda, ~, idx] = unique(round(lam/tol)*tol); % tol でまとめる
    k = numel(uniq_lambda);
    alg_mult = zeros(k,1);
    geom_mult = zeros(k,1);
    for i = 1:k
        lambda_i = uniq_lambda(i);
        alg_mult(i) = sum(lam >= lambda_i - tol & lam <= lambda_i + tol);
        % 幾何学的重複度 = nullity(A - λI)
        M = A - lambda_i*eye(n);
        geom_mult(i) = n - rank(M, tol);
    end
    info.lambda   = uniq_lambda;
    info.alg_mult = alg_mult;
    info.geom_mult= geom_mult;

    if info.is_diagonalizable
        % 対角化データ
        P = V;
        D = Dfull;

        % 検算（P が可逆かどうか）
        Pinv = inv(P);
        info.residual = norm(A - P*D*Pinv, 'fro');

        % 直交対角化の検証（対称なら P は直交）
        if info.is_symmetric
            info.orth_residual = norm(P.'*P - eye(n), 'fro');
        else
            info.orth_residual = NaN;
        end

        % ステップ表示（要点のみ）
        fprintf('--- 固有値（実数） ---\n'); disp(lam.');
        fprintf('rank(V) = %d / n=%d → %s\n', info.rankV, n, ternary(info.is_diagonalizable,'対角化可','不可'));
        if info.is_symmetric
            fprintf('A は実対称：直交固有ベクトル基底が得られます（P''P ≈ I）。\n');
        end
    else
        % 対角化不可（欠陥行列）
        info.residual = NaN;
        info.orth_residual = NaN;

        % 参考：固有値ごとの重複度を表示
        fprintf('--- 固有値ごとの重複度 ---\n');
        for i = 1:k
            fprintf('λ = %.12g : 代数的重複度=%d, 幾何学的重複度=%d\n', ...
                info.lambda(i), info.alg_mult(i), info.geom_mult(i));
        end
    end
end

function out = ternary(cond, a, b)
    if cond, out = a; else, out = b; end
end
