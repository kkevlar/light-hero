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

(write-file "C:\\Users\\kevlar\\out.csv"
            (table->string (transpose (csv->list (make-csv-reader (open-input-file "C:\\Users\\kevlar\\summerair.csv"))))))



