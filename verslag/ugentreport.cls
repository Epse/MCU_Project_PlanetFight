\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{ugentreport}[2019-04-16 Unofficial UGent Report Class]
\LoadClass[a4paper]{article}
\RequirePackage{xcolor}
\RequirePackage{fontspec}
\RequirePackage{titlesec}
\RequirePackage{graphicx}
\RequirePackage{xspace}
\RequirePackage{hyperref}
\RequirePackage{ulem}
\RequirePackage{setspace}

\newcommand{\ugfontname}{UGent Panno Text}
\newcommand{\ugtitlefontname}{UGent Panno Text Medium}

% Options
\DeclareOption{arial}{\renewcommand{\ugfontname}{Arial}}
\DeclareOption{arialtitles}{\renewcommand{\ugtitlefontname}{Arial Black}}
% Send all non-declared options to article
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{article}}
\ProcessOptions\relax

% UGent blauw
\definecolor{ublauw}{HTML}{1E64C8}

% Font setups
\newfontfamily\panno{\ugfontname}
\newfontfamily\ptitle[SizeFeatures={Size=42}]{\ugtitlefontname}
\newfontfamily\psec[Scale=1.3, Color=ublauw]{\ugtitlefontname}

\hypersetup{
  pdftitle=\@title,
  pdfauthor=\@author
}

% Setup headings
\titleformat*{\section}{\Large\psec}
\titleformat*{\subsection}{\large\psec}
\titleformat*{\subsubsection}{\itshape\psec}

\renewcommand{\and}{,\xspace}
\renewcommand{\maketitle}{%
  \begin{titlepage}
    % Dikkere onderlijning
    \renewcommand{\ULthickness}{2pt}%
    \includegraphics[height=1cm]{img/iwa.png} % Logo van faculteit op juiste plaats
    \vspace{2cm}\vfill%
    \begin{minipage}{\textwidth}%
      \ptitle%
      {%
        \color{ublauw}%
        \begin{flushleft}%
          \begin{spacing}{3.5}% The underlines need absurd amounts of line stretch
            \MakeUppercase{\uline{\@title}}%
          \end{spacing}%
        \end{flushleft}%
      }\\%
      \Large{\panno \@author }%
    \end{minipage}%
    \vfill%
    \includegraphics[height=3cm]{img/logo.png} % Logo moet op de juiste plaats
  \end{titlepage}
}