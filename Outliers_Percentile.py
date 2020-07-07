#!/usr/bin/env python
# coding: utf-8

# In[2]:


import numpy as np # linear algebra
import pandas as pd # data processing, CSV file I/O (e.g. pd.read_csv)
import matplotlib.pyplot as plt


Data=pd.read_csv("/Users/khadeejah/Desktop/AB_NYC_2019.csv")
Data.head()


# In[3]:


Data.shape


# In[4]:


Data.describe()


# In[5]:


#Detect the outliers by using percentile
maxthresold=Data['price'].quantile(0.95)
maxthresold


# In[6]:


#remove the outliers
Data[Data['price']>maxthresold]
Data.head()


# In[7]:


#Detect the outliers 
minthresold=Data['price'].quantile(0.05)
minthresold


# In[8]:


#Remove the outliers
Data[Data['price']<minthresold]
Data.head()


# In[9]:


# Data has no outliers
Data_no_outliers=Data[(Data['price']<maxthresold) & (Data['price']>minthresold)]
Data_no_outliers.shape


# In[10]:


Data_no_outliers.describe()


# In[ ]:




