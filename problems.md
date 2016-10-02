---
layout: page
title:  "Problems"
date:   2016-10-02 22:12:25 +0300
categories: environment
---

Problems solved on different websites. Articles will contain task, solution and links to related algorithms,
which should be used, or are just useful for this task.

<ul class="post-list">
  {% for post in site.posts %}
  {% if post.categories contains "problem" %}
    <li>
      <h3>
        <a class="post-link" href="{{ post.url | prepend: site.baseurl }}">{{ post.title }}</a>
      </h3>
    </li>
  {% endif %}
  {% endfor %}
</ul>
