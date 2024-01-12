---
layout: page
title: Participants
description: A list of all participants in the course.
---

# Participants

<!-- Staff information is stored in the `_staffers` directory and rendered according to the layout file, `_layouts/staffer.html`. -->

## Instructor

{% assign instructors = site.staffers | where: 'role', 'Instructor' %}
{% for staffer in instructors %}
{{ staffer }}
{% endfor %}

{% assign Student = site.staffers | where: 'role', 'Student' %}
{% assign Student = students | size %}
{% if Student != 0 %}

## Students

{% for staffer in students %}
{{ staffer }}
{% endfor %}
{% endif %}
