classdef MatrixToolApp < handle

    properties (Access = private)
        % UI
        f                   matlab.ui.Figure
        gridMain            matlab.ui.container.GridLayout

        % 左パネル: 入力
        panelInputs         matlab.ui.container.Panel
        gridInputs          matlab.ui.container.GridLayout
        lblA                matlab.ui.control.Label
        txtA                matlab.ui.control.TextArea
        lblB                matlab.ui.control.Label
        txtB                matlab.ui.control.TextArea
        lblb                matlab.ui.control.Label
        txtb                matlab.ui.control.TextArea

        % 右パネル: 設定 & 実行 & 結果
        panelActions        matlab.ui.container.Panel
        gridRight           matlab.ui.container.GridLayout

        % 設定
        lblTol              matlab.ui.control.Label
        edtTol              matlab.ui.control.EditField
        lblView             matlab.ui.control.Label
        ddView              matlab.ui.control.DropDown

        % 実行ボタン群
        btnDet              matlab.ui.control.Button
        btnInv              matlab.ui.control.Button
        btnRref             matlab.ui.control.Button
        btnRank             matlab.ui.control.Button
        btnSolve            matlab.ui.control.Button
        btnMul              matlab.ui.control.Button
        btnAll              matlab.ui.control.Button
        btnClear            matlab.ui.control.Button

        % 結果表示
        lblResult           matlab.ui.control.Label
        txtResult           matlab.ui.control.TextArea
    end

    methods
        function app = MatrixToolApp()
            % コンストラクタ: UI 構築
            buildUI(app);
            % 既定のサンプル
            app.txtA.Value = ["[1 2; 3 4]"];
            app.txtB.Value = ["[5 -1; 2  0]"];
            app.txtb.Value = ["[1; 0]"];
            app.updateDefaultTol();
            app.appendLine("ようこそ！左で A, B, b を入力し、右のボタンで計算します。");
        end
    end

    %% ===== UI構築 =====
    methods (Access = private)
        function buildUI(app)
            app.f = uifigure( ...
                'Name','Matrix Tool App', ...
                'Position',[100 100 1100 720], ...
                'Scrollable','on');

            app.gridMain = uigridlayout(app.f, [1 2]);
            app.gridMain.ColumnWidth = {'1x','1.2x'};
            app.gridMain.Padding = [10 10 10 10];
            app.gridMain.RowHeight = {'1x'};

            % 左: 入力
            app.panelInputs = uipanel(app.gridMain, 'Title','入力（A, B, b）');
            app.panelInputs.FontWeight = 'bold';
            app.gridInputs = uigridlayout(app.panelInputs, [6 1]);
            app.gridInputs.RowHeight = {22,'2x',22,'2x',22,'1.5x'};
            app.gridInputs.Padding = [8 8 8 8];
            app.gridInputs.RowSpacing = 6;

            app.lblA = uilabel(app.gridInputs, 'Text','行列 A（例: [1 2; 3 4]）:');
            app.txtA = uitextarea(app.gridInputs, ...
                'FontName','Consolas','FontSize',12, ...
                'Value', {''}, ...
                'ValueChangedFcn', @(~,~)app.updateDefaultTol());

            app.lblB = uilabel(app.gridInputs, 'Text','行列 B（行列積 A*B 用）:');
            app.txtB = uitextarea(app.gridInputs, ...
                'FontName','Consolas','FontSize',12, ...
                'Value', {''});

            app.lblb = uilabel(app.gridInputs, 'Text','ベクトル/行列 b（Ax=b 用）:');
            app.txtb = uitextarea(app.gridInputs, ...
                'FontName','Consolas','FontSize',12, ...
                'Value', {''});

            % 右: 設定・実行・結果
            app.panelActions = uipanel(app.gridMain, 'Title','設定・実行・結果');
            app.panelActions.FontWeight = 'bold';

            % 行の競合を避けて再配置（8行×2列）
            app.gridRight = uigridlayout(app.panelActions, [8 2]);
            app.gridRight.RowHeight   = {22, 34, 38, 38, 38, 38, 38, '1x'};
            app.gridRight.ColumnWidth = {'1x','1x'};
            app.gridRight.Padding = [8 8 8 8];
            app.gridRight.RowSpacing = 6;
            app.gridRight.ColumnSpacing = 8;

            % 設定行
            app.lblTol = uilabel(app.gridRight, 'Text','tol (rref/rank):');
            app.lblTol.Layout.Row = 1; app.lblTol.Layout.Column = 1;

            app.edtTol = uieditfield(app.gridRight,'text','Value','');
            app.edtTol.Layout.Row = 1; app.edtTol.Layout.Column = 2;

            app.lblView = uilabel(app.gridRight,'Text','表示モード:');
            app.lblView.Layout.Row = 2; app.lblView.Layout.Column = 1;

            app.ddView = uidropdown(app.gridRight, ...
                'Items', {'numeric','rational'}, ...
                'Value', 'numeric');
            app.ddView.Layout.Row = 2; app.ddView.Layout.Column = 2;

            % ボタン列
            app.btnDet  = uibutton(app.gridRight, 'Text','det(A)',   'ButtonPushedFcn', @(~,~)app.onDet());
            app.btnDet.Layout.Row = 3; app.btnDet.Layout.Column = 1;

            app.btnInv  = uibutton(app.gridRight, 'Text','inv(A)',   'ButtonPushedFcn', @(~,~)app.onInv());
            app.btnInv.Layout.Row = 3; app.btnInv.Layout.Column = 2;

            app.btnRref = uibutton(app.gridRight, 'Text','RREF(A)',  'ButtonPushedFcn', @(~,~)app.onRref());
            app.btnRref.Layout.Row = 4; app.btnRref.Layout.Column = 1;

            app.btnRank = uibutton(app.gridRight, 'Text','rank(A)',  'ButtonPushedFcn', @(~,~)app.onRank());
            app.btnRank.Layout.Row = 4; app.btnRank.Layout.Column = 2;

            app.btnSolve= uibutton(app.gridRight, 'Text','Solve  Ax=b', 'ButtonPushedFcn', @(~,~)app.onSolve());
            app.btnSolve.Layout.Row = 5; app.btnSolve.Layout.Column = 1;

            app.btnMul  = uibutton(app.gridRight, 'Text','Multiply  A*B', 'ButtonPushedFcn', @(~,~)app.onMultiply());
            app.btnMul.Layout.Row = 5; app.btnMul.Layout.Column = 2;

            app.btnAll  = uibutton(app.gridRight, 'Text','まとめて（det/inv/RREF/rank）', ...
                'ButtonPushedFcn', @(~,~)app.onAll());
            app.btnAll.Layout.Row = 6; app.btnAll.Layout.Column = [1 2];

            app.btnClear= uibutton(app.gridRight, 'Text','出力クリア', 'ButtonPushedFcn', @(~,~)app.onClear());
            app.btnClear.Layout.Row = 7; app.btnClear.Layout.Column = [1 2];

            app.lblResult = uilabel(app.gridRight, 'Text','結果:');
            app.lblResult.Layout.Row = 8; app.lblResult.Layout.Column = [1 2];

            app.txtResult = uitextarea(app.gridRight, ...
                'FontName','Consolas','FontSize',12, ...
                'Editable','off','Value', {''});
            app.txtResult.Layout.Row = 8; app.txtResult.Layout.Column = [1 2];
        end
    end

    %% ===== コールバック（実行） =====
    methods (Access = private)
        function onDet(app)
            try
                A = app.parseMatrix(app.txtA.Value, 'A');
                app.appendHeader('det(A)');
                if ~app.isSquare(A)
                    app.appendError(sprintf('det(A) は正方行列のみ（サイズ: %dx%d）。', size(A,1), size(A,2))); return;
                end
                d = det(A);
                app.printMatrix(A,'A');
                app.appendLine(sprintf('det(A) = %.16g', d));
            catch ME
                app.appendError(ME.message);
            end
        end

        % 逆行列計算
        function onInv(app)
            try
                A = app.parseMatrix(app.txtA.Value, 'A');
                app.appendHeader('inv(A)');
                % 正方行列ではない場合
                if ~app.isSquare(A)
                    app.appendError(sprintf('inv(A) は正方行列のみ（サイズ: %dx%d）。', size(A,1), size(A,2))); return;
                end
                % 正則行列ではない場合
                d = det(A);
                if abs(d) == 0
                    app.appendError('det(A)=0 のため逆行列は存在しません。'); return;
                end
                n = size(A,1);
                invSolve = A \ eye(n);
                invDirect = inv(A);
                app.printMatrix(A,'A');
                app.printMatrix(invSolve,'inv(A)（A\\I）');
                app.printMatrix(invDirect,'inv(A)（inv）');
                app.safeAppendCond(A);
            catch ME
                app.appendError(ME.message);
            end
        end
        
        % 簡約化計算
        function onRref(app)
            try
                A = app.parseMatrix(app.txtA.Value, 'A');
                app.appendHeader('RREF(A)');
                tol = app.getTol(A);
                [R, piv] = rref(A, tol);
                app.printMatrix(A,'A');
                app.printMatrix(R,'RREF(A)');
                app.appendLine(sprintf('ピボット列: %s', mat2str(piv)));
            catch ME
                app.appendError(ME.message);
            end
        end

        % 階数計算
        function onRank(app)
            try
                A = app.parseMatrix(app.txtA.Value, 'A');
                app.appendHeader('rank(A)');
                tol = app.getTol(A);
                r = rank(A, tol);
                app.printMatrix(A,'A');
                app.appendLine(sprintf('rank(A) = %d (tol = %.3g)', r, tol));
            catch ME
                app.appendError(ME.message);
            end
        end

        % 1次連立方程式計算
        function onSolve(app)
            try
                A = app.parseMatrix(app.txtA.Value, 'A');
                b = app.parseMatrix(app.txtb.Value, 'b');
                [m,n] = size(A);
                app.appendHeader('Ax=b');
                if size(b,1) ~= m
                    app.appendError(sprintf('サイズ不一致: b の行数は %d 必要（現在 %d）。', m, size(b,1))); return;
                end
                tol = app.getTol(A);
                rA   = rank(A, tol);
                rAug = rank([A b], tol);
                app.printMatrix(A,'A'); app.printMatrix(b,'b');
                app.appendLine(sprintf('rank(A)=%d, rank([A b])=%d, size(A)=%dx%d, tol=%.3g', rA, rAug, m, n, tol));

                if rAug > rA
                    % 不整合 → 最小二乗
                    app.appendError('系は不整合（解なし）。最小二乗解を返します。');
                    x = A \ b;
                    app.printMatrix(x,'x_{LS}');
                    res = A*x - b;
                    app.appendLine(sprintf('||Ax - b||_2 = %.6e', norm(res,2)));
                    return;
                end

                % 整合
                if rA == n && m >= n
                    % 唯一解
                    app.appendLine('唯一解が存在します。');
                    x = A \ b;
                    app.printMatrix(x,'x（唯一解）');
                    res = A*x - b;
                    app.appendLine(sprintf('||Ax - b||_2 = %.6e', norm(res,2)));
                    if m==n, app.safeAppendCond(A); end
                else
                    % 無限解 → 最小ノルム解 & 一般解
                    app.appendLine('解は無限に存在します（欠損ランク）。');
                    x0 = pinv(A)*b;
                    app.printMatrix(x0,'x_0（最小ノルム解）');
                    Z = null(A, 'r');
                    if isempty(Z)
                        app.appendLine('null(A) は空（数値的に極小）。');
                    else
                        app.printMatrix(Z,'null(A) の基底行列 Z');
                        app.appendLine('一般解: x = x_0 + Z*y  （y は任意ベクトル）');
                    end
                    res = A*x0 - b;
                    app.appendLine(sprintf('（最小ノルム解の）||A*x_0 - b||_2 = %.6e', norm(res,2)));
                end
            catch ME
                app.appendError(ME.message);
            end
        end

        % 行列の積計算
        function onMultiply(app)
            try
                A = app.parseMatrix(app.txtA.Value, 'A');
                B = app.parseMatrix(app.txtB.Value, 'B');
                app.appendHeader('A * B');
                if size(A,2) ~= size(B,1)
                    app.appendError(sprintf('サイズ不一致: Aは %dx%d, Bは %dx%d。列数(A)と行数(B)が一致必要。', ...
                        size(A,1), size(A,2), size(B,1), size(B,2)));
                    return;
                end
                C = A * B;
                app.printMatrix(A,'A');
                app.printMatrix(B,'B');
                app.printMatrix(C,'A*B');
            catch ME
                app.appendError(ME.message);
            end
        end

        % まとめて計算を行うソルバ
        function onAll(app)
            try
                A = app.parseMatrix(app.txtA.Value, 'A');
                app.appendHeader('まとめて: det/inv/RREF/rank');
                % det
                if app.isSquare(A)
                    app.appendLine(sprintf('[1] det(A) = %.16g', det(A)));
                else
                    app.appendLine('[1] det(A): 非正方のためスキップ');
                end
                % inv
                if app.isSquare(A) && abs(det(A))~=0
                    n = size(A,1);
                    invA = A \ eye(n);
                    app.printMatrix(invA,'[2] inv(A)');
                else
                    app.appendLine('[2] inv(A): 非正方または特異のためスキップ');
                end
                % RREF
                tol = app.getTol(A);
                [R, piv] = rref(A, tol);
                app.printMatrix(R,'[3] RREF(A)');
                app.appendLine(sprintf('    ピボット列: %s', mat2str(piv)));
                % rank
                r = rank(A, tol);
                app.appendLine(sprintf('[4] rank(A) = %d (tol=%.3g)', r, tol));
            catch ME
                app.appendError(ME.message);
            end
        end

        function onClear(app)
            app.txtResult.Value = {''};
        end
    end

    %% ===== ヘルパ =====
    methods (Access = private)
        function A = parseMatrix(app, textLines, name)
            % TextArea 複数行を結合して評価（数値行列化）
            txt = strjoin(string(textLines), " ");
            txt = strtrim(txt);
            if isempty(txt), error(sprintf('%s が空です。', name)); end %#ok<SPERR>
            A = str2num(txt); %#ok<ST2NM>
            if isempty(A) || ~isnumeric(A)
                error(sprintf('%s の入力を数値行列として解釈できません。例: [1 2; 3 4]', name));
            end
            if ~ismatrix(A)
                error(sprintf('%s は2次元行列である必要があります。', name));
            end
        end

        function tf = isSquare(~, A)
            s = size(A);
            tf = (numel(s)==2 && s(1)==s(2));
        end

        function tol = getTol(app, A)
            % EditField の tol が空なら既定 tol を推定
            t = strtrim(app.edtTol.Value);
            if isempty(t)
                tol = max(size(A)) * eps(norm(A,'fro'));
            else
                v = str2double(t);
                if ~isfinite(v) || v<=0
                    error('tol は正の実数で入力してください。');
                end
                tol = v;
            end
        end

        function updateDefaultTol(app)
            % A の現在値から既定 tol を見積もって表示（参考）
            try
                A = app.parseMatrix(app.txtA.Value,'A');
                tol = max(size(A)) * eps(norm(A,'fro'));
                app.edtTol.Value = sprintf('%.3g', tol);
            catch
                app.edtTol.Value = '';
            end
        end

        function mode = viewMode(app)
            mode = app.ddView.Value; % 'numeric' or 'rational'
        end

        function printMatrix(app, X, name)
            app.appendLine(sprintf('%s:', name));
            switch app.viewMode()
                case 'numeric'
                    app.appendValue(X);
                otherwise
                    app.appendLines(strsplit(string(rats(X)), newline));
            end
        end

        function safeAppendCond(app, A)
            try
                c = cond(A);
                app.appendLine(sprintf('cond(A) = %.3e', c));
            catch
            end
        end

        % ===== 出力補助 =====
        function appendHeader(app, titleText)
            app.appendLine('');
            app.appendLine(repmat('=',1, max(8, numel(titleText))));
            app.appendLine(titleText);
            app.appendLine(repmat('=',1, max(8, numel(titleText))));
        end

        function appendLine(app, s)
            if isstring(s) || ischar(s)
                app.txtResult.Value = [app.txtResult.Value; {char(s)}];
            else
                app.appendValue(s);
            end
        end

        function appendLines(app, cellStr)
            v = app.txtResult.Value;
            for i = 1:numel(cellStr)
                v = [v; {char(cellStr{i})}]; %#ok<AGROW>
            end
            app.txtResult.Value = v;
        end

        function appendValue(app, val)
            if isnumeric(val) || islogical(val)
                str = app.matrixToString(val, 12);
                app.appendLines(strsplit(str, newline));
            else
                app.appendLine(evalc('disp(val)')); %#ok<EVLC>
            end
        end

        function s = matrixToString(~, M, width)
            if nargin<3, width = 12; end
            if isempty(M)
                s = "[]"; return;
            end
            fmt = sprintf('%%%d.6g', width);
            lines = strings(size(M,1),1);
            for i = 1:size(M,1)
                row = strings(1,size(M,2));
                for j = 1:size(M,2)
                    row(j) = sprintf(fmt, M(i,j));
                end
                lines(i) = "[" + strjoin(row," ") + "]";
            end
            s = strjoin(lines, newline);
        end
    end
end
