from django.db import models


class Cache(models.Model):
    ip = models.CharField(max_length=25, null=True, blank=True)
    total_calls = models.IntegerField(default=0, null=True, blank=True)
    Date = models.CharField(max_length=50, null=True, blank=True)

    def __str__(self):
        return self.ip
