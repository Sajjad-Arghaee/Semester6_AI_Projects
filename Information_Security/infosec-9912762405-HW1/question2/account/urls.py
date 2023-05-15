from django.urls import path
from . import views

urlpatterns = [
    path('', views.rate_limiter, name='rate_limiter'),
]
