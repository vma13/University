Diplom::Application.routes.draw do
   
  #http://www.railslodge.com/plugins/75-restful-authentication/documentations/1-change-password
  #http://markconnell.co.uk/posts/2010/02/rails-3-routing-examples
   
  resources :schools, :school_groups, :disciplines, :users    
 
  resources :users do
    post :change_session_year,  :on => :collection
    get  :change_user_password, :on => :member
  end
  
  resources :statements do 
   resources :marks
  end 
  
   resources :groups do
    post :save_data, :on => :member
    get  :generate,  :on => :member    
    get :mark, :on => :member    
    get :pres, :on => :member    
    get :res,  :on => :member
    post :create_mark, :on=>:member
    post :create_pres, :on=>:member
    post :create_res,  :on=>:member
    get :stat, :on => :member
  end
   


  resources :courses do
    member do
      post :save_data
      get :generate
    end    
  end
  
  resources :schoolkids do
    collection do
      get :search
      post :change_session_year
    end
  end

  resource :session, :only => [:new, :create, :destroy]
     
  match 'signup' => 'users#new', :as => :signup

  match 'register' => 'users#create', :as => :register

  match 'login' => 'sessions#new', :as => :login
  
  match 'logout' => 'sessions#destroy', :as => :logout

  match '/activate/:activation_code' => 'users#activate', :as => :activate, :activation_code => nil

  # The priority is based upon order of creation:
  # first created -> highest priority.

  # Sample of regular route:
  #   match 'products/:id' => 'catalog#view'
  # Keep in mind you can assign values other than :controller and :action

  # Sample of named route:
  #   match 'products/:id/purchase' => 'catalog#purchase', :as => :purchase
  # This route can be invoked with purchase_url(:id => product.id)

  # Sample resource route (maps HTTP verbs to controller actions automatically):
  #   resources :products

  # Sample resource route with options:
  #   resources :products do
  #     member do
  #       get 'short'
  #       post 'toggle'
  #     end
  #
  #     collection do
  #       get 'sold'
  #     end
  #   end

  # Sample resource route with sub-resources:
  #   resources :products do
  #     resources :comments, :sales
  #     resource :seller
  #   end

  # Sample resource route with more complex sub-resources
  #   resources :products do
  #     resources :comments
  #     resources :sales do
  #       get 'recent', :on => :collection
  #     end
  #   end

  # Sample resource route within a namespace:
  #   namespace :admin do
  #     # Directs /admin/products/* to Admin::ProductsController
  #     # (app/controllers/admin/products_controller.rb)
  #     resources :products
  #   end

  # You can have the root of your site routed with "root"
  # just remember to delete public/index.html.
  root :to => "schoolkids#index"

  # See how all your routes lay out with "rake routes"

  # This is a legacy wild controller route that's not recommended for RESTful applications.
  # Note: This route will make all actions in every controller accessible via GET requests.
  # match ':controller(/:action(/:id(.:format)))'
end
