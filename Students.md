---
layout: page
title: Students
description: A list of all participants in the course.
---

<!-- Staff information is stored in the `_staffers` directory and rendered according to the layout file, `_layouts/staffer.html`. -->

{% assign students = site.staffers | where: 'role', 'Student' %}
{% assign num_students = students | size %}
{% if num_students != 0 %}

## Students

{% for staffer in students %}
{{ staffer }}
{% endfor %}
{% endif %}

## Instructor

{% assign instructors = site.staffers | where: 'role', 'Instructor' %}
{% for staffer in instructors %}
{{ staffer }}
{% endfor %}
