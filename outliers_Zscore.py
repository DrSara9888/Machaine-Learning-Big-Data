#!/usr/bin/env python
# coding: utf-8

# In[2]:


import numpy as np # linear algebra
import pandas as pd # data processing, CSV file
from matplotlib import pyplot as plt
get_ipython().run_line_magic('matplotlib', 'inline')
import seaborn as sns


# In[3]:


Data=pd.read_csv("/Users/khadeejah/Desktop//Bengaluru_House_Data.csv")
Data.head()


# In[4]:


# Use log Scale
plt.hist(Data.price, bins=20, rwidth=0.8)
plt.xlabel('Price')
plt.ylabel('Count')
plt.yscale('log')
plt.show()


# In[5]:


#Detect the outliers
maxlimit=Data["price"].quantile(0.999)
maxlimit


# In[6]:


#Remove the outliers
Data[Data["price"]>maxlimit]


# In[7]:


# Detect the outliers
minlimit=Data["price"].quantile(0.0001)
minlimit


# In[8]:


# Remove the outliers
Data[Data["price"]<minlimit]


# In[9]:


Data_outliers=Data[(Data["price"]>minlimit)|(Data["price"]<maxlimit)]
Data_outliers.head()


# In[10]:


#Data with no outliers by using Percentile outliers removal
Data2=Data[(Data["price"]>minlimit)& (Data["price"]<maxlimit)]
Data2.head()


# In[11]:


Data.shape[0] - Data2.shape[0]


# In[12]:


plt.figure(figsize=(20,8))

plt.subplot(1,2,1)
plt.hist(Data2.price, bins=20, rwidth=0.8)
plt.xlabel('price')
plt.ylabel('Count')
plt.yscale('log')
plt.show

plt.subplot(1,2,2)
sns.distplot(Data2.price)


# In[13]:


from scipy.stats import norm
import numpy as np
plt.hist(Data2.price, bins=20, rwidth=0.8, density=True)
plt.xlabel('Price')
plt.ylabel('Count')

rng = np.arange(-1000, Data2.price.max(), 100)
plt.plot(rng, norm.pdf(rng,Data2.price.mean(),Data2.price.std()))


# In[14]:


Data2.describe()


# In[15]:


Data2.price.mean()


# In[16]:


Data2.price.std()


# In[17]:


upper_limit = Data2.price.mean() + 4*Data2.price.std()
upper_limit


# In[18]:


lower_limit =Data2.price.mean()-4*Data2.price.std()
lower_limit


# In[19]:


#the outliers that are beyond 4 std dev from mean
Data2[(Data2.price>upper_limit) | (Data2.price<lower_limit)]


# In[20]:


#Outliers removal by using Standard Deviation Data without outliers
Data3=Data2[(Data2.price<upper_limit) & (Data2.price>lower_limit)]
Data3.head()


# In[21]:


Data.shape


# In[22]:


Data2.shape


# In[23]:


Data3.shape


# In[24]:


from scipy.stats import norm
import numpy as np
plt.hist(Data3.price, bins=20, rwidth=0.8, density=True)
plt.xlabel('Price')
plt.ylabel('Count')

rng = np.arange(-600, Data3.price.max(), 100)
plt.plot(rng, norm.pdf(rng,Data3.price.mean(),Data3.price.std()))


# In[25]:


#Outliers Detection and Removal by using Z score Z= Data-mean/standard deviation
Data2["zscore"]=(Data2.price-Data2.price.mean())/Data2.price.std()
Data2.head()


# In[26]:


#data points that has z score higher than 4 or lower than -4. Another way of saying same thing is get data points that are more than 4 standard deviation away

Data2[Data2["zscore"]>4]


# In[27]:


Data2[Data2['zscore']<-4]


# In[28]:


# outliers
Data2[(Data2.zscore<-4)|(Data2.zscore>4)]


# In[29]:


# Remove the outliers from the Data points
Data4= Data2[(Data2.zscore>-4)&(Data2.zscore<4)]
Data4.head()


# In[30]:


Data3.shape


# In[31]:


Data4.shape


# In[32]:


Data2.shape[0] - Data4.shape[0]


# In[33]:


Data2.shape[0] - Data3.shape[0]


# In[ ]:




