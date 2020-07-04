#!/usr/bin/env python
# coding: utf-8

# In[2]:


#Linear Regression Feature Importance
import sklearn
from sklearn.datasets import make_regression
from sklearn.linear_model import LinearRegression
from matplotlib import pyplot

# define  the dataset
X,y= make_regression(n_samples=1000, n_features=10,n_informative=5,random_state=1) 
#defien the model
model=LinearRegression()
#fit the model
model.fit(X,y)
#get importance
importance=model.coef_
#summarize features importance
for i,v in enumerate(importance):
    print('Feature:%0d,Score: %.5f' %(i,v))
# plot fearure importance
pyplot.bar([x for x in range (len(importance))], importance)
pyplot.show()


# In[6]:


# logistic Regresstion for future importance
from sklearn.datasets import make_classification
from sklearn.linear_model import LogisticRegression
#define the Data set
X,y= make_classification(n_samples=1000, n_features=10, n_informative=5,n_redundant=5, random_state=1)
#define the model
model=LogisticRegression()
#fit the model
model.fit(X,y)
#get importance
importance = model.coef_[0]
#summarize feature importancefor 
for i,v in enumerate(importance):
    print('Feature: %0d  ,Score: %.5f',(i,v))
# plot feature importance
pyplot.bar([x for x in range(len(importance))],importance)
pyplot.show()


# In[8]:


#Desision Tree for features importance on a regresstion problem 
from sklearn.datasets import make_regression
from sklearn.tree import DecisionTreeRegressor
from matplotlib import pyplot

#define the dataset
X,y=make_regression(n_samples=1000, n_features=10, n_informative=5, random_state=1)
#definethe model
model= DecisionTreeRegressor()
#fit the model
model.fit(X,y)
#get the importance
importance=model.feature_importances_
#summrize feature importance
for i,v in enumerate(importance):
    print('Feature:%0d   ,Score  %.5f:  ' %(i,v))
#plot feature importance
pyplot.bar([ x for x in range(len(importance))],importance)
pyplot.show()


# In[13]:


#decision tree for feature importance on a regression problem
from sklearn.datasets import make_classification
from sklearn.tree import DecisionTreeClassifier
# define the dataset
X,y=make_classification(n_samples=1000,n_features=10,n_informative=5, random_state=1)
#define the model
model=DecisionTreeClassifier()
#fit the model
model.fit(X,y)
#get importancabse
importance=model.feature_importances_
#summarize feature importance
for i,v in enumerate(importance):
    print('Feature: %0d, Score:%.5f' %(i,v))
#plot feature importane
pyplot.bar([x for x in range(len(importance))],importance)
pyplot.show()


# In[18]:


# Randome feature importance
from sklearn.datasets import make_regression
from sklearn.ensemble import RandomForestRegressor 

# define the Dataset
X,y=make_regression(n_samples=1000,n_features=10,n_informative=5,random_state=1)
#define the model
model=RandomForestRegressor()
#fit the model
model.fit(X,y)
#get the importance Features
importance=model.feature_importances_

for i,v in enumerate(importance):
    print('Feature: %0d, Score:%.5f' %(i,v))
# plot features importance
pyplot.bar([x for x in range(len(importance))] ,importance)
pyplot.show()


# In[19]:


#Random forest features importance on classification problem
from sklearn.datasets import make_classification
from sklearn.ensemble import RandomForestClassifier

#define the Dataset
X,y=make_classification(n_samples=1000, n_features=10, n_informative=5, n_redundant=5,random_state=1)
#define the model
model=RandomForestClassifier()
#fit the model
model.fit(X,y)
#get the importancabse
importance=model.feature_importances_
#summarize features importance
for i,v in enumerate(importance):
    print('Feature: %0d, Score: %.5f' %(i,v))
 # plot feature importance
pyplot.bar([x for x in range(len(importance))], importance)
pyplot.show()   


# In[27]:


from sklearn.datasets import make_regression
from sklearn.neighbors import KNeighborsRegressor
from sklearn.inspection import permutation_importance
from matplotlib import pyplot
# define dataset
X, y = make_regression(n_samples=1000, n_features=10, n_informative=5, random_state=1)
#define the model
model=KNeighborsRegressor()
#fit thr model
model.fit(X,y)
# perform permutation importance
results=permutation_importance(model,X,y,scoring='neg_mean_squared_error')
#get importance
importance = results.importances_mean

# summarize feature importance
for i,v in enumerate(importance):
    print('Feature: %0d, Score: %.5f' % (i,v))
# plot feature importance
pyplot.bar([x for x in range(len(importance))], importance)
pyplot.show()


# In[ ]:




