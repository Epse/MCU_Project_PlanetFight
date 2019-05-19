(TeX-add-style-hook
 "doc"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("article" "a4paper")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("babel" "dutch")))
   (TeX-run-style-hooks
    "latex2e"
    "article"
    "art10"
    "babel"
    "hyperref"
    "parskip"))
 :latex)

