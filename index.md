---
layout: default
title: "손정원의 실험노트"
---

# Welcome to my blog!

이 블로그에는 제가 해냈던 기록들을 담고자 합니다.<br>
저는 손정원(JungWon Sohn)입니다. David Sohn도 제 이름입니다.<br>
davidsohn-yonsei 가 제 깃허브 계정입니다.

<br>

Hello, there!<br>
My name is JungWon Sohn. David Sohn is also my name.<br>
davidsohn-yonsei is my github account.

<br>


---

<br>

## Posts
<ul>
  {% for post in site.posts %}
    <li>
      <a href="{{ post.url | relative_url }}">{{ post.title }}</a>
      <small>({{ post.date | date: "%Y-%m-%d" }})</small>
    </li>
  {% endfor %}
</ul>
