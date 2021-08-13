from selenium import webdriver
from selenium.webdriver.common import keys
import time
import requests
import random


# 创建浏览器
def functions():
    browser = webdriver.Chrome(r'E:\taobao\chromedriver.exe')
    # 让浏览器打开淘宝
    browser.get("https://www.taobao.com/")

    # 找到搜索框输入内容并搜索
    browser.find_element_by_xpath('//*[@id="q"]').send_keys("A4纸", keys.Keys.ENTER)
    time.sleep(1)
    # 切换成二维码登录
    browser.find_element_by_xpath('//*[@id="login"]/div[1]/i').click()

    # 判断当前页面是否为登录页面
    while browser.current_url.startswith("https://login.taobao.com/"):
        print("等待用户输入")
        time.sleep(1)

    print("登录成功!!!")
    n = 1
    count = 1

    while True:
        items = browser.find_elements_by_css_selector('.m-itemlist .items > div')
        for item in items:
            # 获取这张图片的下载地址
            img = item.find_element_by_css_selector(".pic-box .pic img").get_attribute("data-src")
            # 拼接完成的下载地址
            img_url = "http:" + img
            # print(img_url)
            # 通过requests下载这张图片
            sleep_time = random.random()*10
            time.sleep(sleep_time)
            # 文件夹需要手动创建好
            file = open(f"E:\\taobao_A4\\{n}.jpg", "wb")
            file.write(requests.get(img_url).content)
            print("下载图片" + str(n))
            n += 1

        # 翻页操作
        browser.find_element_by_css_selector('.wraper:nth-last-child(1) .next > a').click()
        time.sleep(2)
        count += 1
        # 爬取 4 页内容
        if count == 6:
            # file.close()
            break

    # 关闭浏览器
    browser.quit()


if __name__ == '__main__':
    functions()

