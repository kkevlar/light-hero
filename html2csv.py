from bs4 import BeautifulSoup
import urllib2
import csv

url = 'http://www.data.jma.go.jp/obd/stats/etrn/view/monthly_s3_en.php?block_no=47401&view=1'
html = urllib2.urlopen(url).read()
soup = BeautifulSoup(html)
table = soup.select_one("table.data2_s")
# python3 just use th.text
headers = [th.text.encode("utf-8") for th in table.select("tr th")]

with open("out.csv", "w") as f:
    wr = csv.writer(f)
    wr.writerow(headers)
    wr.writerows([[td.text.encode("utf-8") for td in row.find_all("td")] for row in table.select("tr + tr")])
    