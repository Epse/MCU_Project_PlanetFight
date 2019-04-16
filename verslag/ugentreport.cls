\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{ugentreport}[2019-04-16 Unofficial UGent Report Class]
\LoadClass[a4paper]{article}
\RequirePackage{xcolor}
\RequirePackage{fontspec}
\RequirePackage{soul}
\RequirePackage{titlesec}
\RequirePackage{graphicx}
\RequirePackage{xspace}

\newcommand{\ugfontname}{Panno Text}
\newcommand{\ugtitlefontname}{Panno Text Medium}

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
\newfontfamily\ptitle[SizeFeatures={Size=30}]{\ugtitlefontname}
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
    \setul{}{2pt} % Dikkere onderlijning
    \setuldepth{j} % Beetje ruimte, maar niet zo bizar veel
    \includegraphics[height=1cm]{img/iwa.png} % Logo van faculteit op juiste plaats
    \vspace{2cm} \vfill%

    % The mbox is to make it never hyphenate (soul breaks on that)
    % All of the comments are to avoid newline spacing
    \textcolor{ublauw}{\ptitle \uppercase{\ul{%
          \mbox{\@title}%
        }}}\\[1em]%
    \Large{\panno \@author }%
    \vfill%
    \includegraphics[height=3cm]{img/logo.png} % Logo moet op de juiste plaats
  \end{titlepage}
}