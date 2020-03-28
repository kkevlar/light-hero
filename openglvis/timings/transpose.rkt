#lang racket

(require csv-reading)
(require csv-writing)
 (require 2htdp/batch-io)

(define (transpose xss)
  (apply map list xss))

(define make-csv-reader
  (make-csv-reader-maker
   '((separator-chars            #\,)
     (strip-leading-whitespace?  . #t)
     (strip-trailing-whitespace? . #t))))

(define table (transpose (csv->list (make-csv-reader (open-input-file "summerair.csv")))))

(define (fixit el)
  (cond
    [(char-alphabetic? (first (string->list el))) (string-append "'" el "'")]
    [else el]))

(define chared-table (map (λ (row) (map fixit row)) table))

(write-file "t-summerair.csv" (table->string chared-table))
            



