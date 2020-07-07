#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np # linear algebra
import pandas as pd 
import seaborn as sns
import matplotlib.pyplot as plt
get_ipython().run_line_magic('matplotlib', 'inline')


# In[2]:


Data=pd.read_csv("/Users/khadeejah/Desktop/weight-height.csv")
Data.head()


# In[3]:


#Scatter plot to show the outliers
plt.figure(figsize=(20,8))
plt.scatter(Data.Weight,Data.Height)
plt.xlabel('Weight')
plt.ylabel('Height')
plt.show()


# In[4]:


Data.describe()


# In[5]:


#Height Plot Distrbution
plt.figure(figsize=(20,8))

plt.subplot(1,3,1)
sns.distplot(Data.Height)
plt.ylabel('Distrbution')

plt.subplot(1,3,2)
sns.boxplot(y=Data.Height)

plt.subplot(1,3,3)
plt.hist(Data.Height, bins=20, rwidth=0.8)
plt.xlabel('Height')
plt.ylabel('Count')

plt.show()


# In[6]:


Q1=Data.Height.quantile(0.25)
Q3=Data.Height.quantile(0.75)
Q1,Q3


# In[7]:


IQR=Q3-Q1
IQR


# In[8]:


lower_limit=Q1-1.5*IQR
Upper_limit=Q3+1.5*IQR
lower_limit,Upper_limit


# In[9]:


#Height outliers
Data_outlier=Data[(Data.Height<lower_limit)|(Data.Height>Upper_limit)]
Data_outlier


# In[11]:


Data_no_outlier=Data[(Data.Height>lower_limit)&(Data.Height<Upper_limit)]
Data_no_outlier.head(3)


# In[12]:


#Weight Plot Distrbution
plt.figure(figsize=(20,8))

plt.subplot(1,3,1)
sns.distplot(Data.Weight)
plt.ylabel('Distrbution')

plt.subplot(1,3,2)
sns.boxplot(y=Data.Weight)

plt.subplot(1,3,3)
plt.hist(Data.Weight, bins=20, rwidth=0.8)
plt.xlabel('Weight')
plt.ylabel('Count')
plt.show()


# In[13]:


Q1=Data.Weight.quantile(0.25)
Q3=Data.Weight.quantile(0.75)
Q1,Q3


# In[14]:


IQR=Q3-Q1
IQR


# In[15]:


Weight_lower_limit=Q1-1.5*IQR
Weight_Upper_limit=Q3+1.5*IQR
Weight_lower_limit,Weight_Upper_limit


# In[16]:


# Weight outliers
Data_outlier=Data[(Data.Weight<Weight_lower_limit)|(Data.Weight>Weight_Upper_limit)]
Data_outlier


# In[18]:


Data_no_outlier=Data[(Data.Weight>Weight_lower_limit)&(Data.Weight<Weight_Upper_limit)]
Data_no_outlier.head()


# In[ ]:




