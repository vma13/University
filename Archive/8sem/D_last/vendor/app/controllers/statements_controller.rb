class StatementsController < ApplicationController
  
   before_filter :check_admin_user
  
  # GET /statements
  # GET /statements.json
  
  def index
    respond_to do |format|
      format.html {
        @statements = Statement.page(params[:page])
        @schoolkids = Schoolkid.page(params[:page])
      }
      format.json do
        @statements = Statement.where("lower(value) LIKE lower(?)","%#{params[:q]}%").all
        render :json=>@statements.map(&:attributes)
      end
    end
  end

  # GET /statements/1
  # GET /statements/1.json
  def show
    @statement = Statement.find(params[:id])

    respond_to do |format|
      format.html # show.html.erb
      format.json { render :json => @statement }
    end
  end

  # GET /statements/new
  # GET /statements/new.json
  def new
    @statement = Statement.new

    respond_to do |format|
      format.html # new.html.erb
      format.json { render :json => @statement }
    end
  end

  # GET /statements/1/edit
  def edit
    @statement = Statement.find(params[:id])
  end

  # POST /statements
  # POST /statements.json
  def create
    @statement = Statement.new(params[:statement])
   
    respond_to do |format|
      if @statement.save
        redirect_to statements_path, :notice => 'Statement was successfully created.'
        return
      else
        format.html { render :action => "new" }
      end
    end
  end

  # PUT /statements/1
  # PUT /statements/1.json
  def update
    @statement = Statement.find(params[:id])

    respond_to do |format|
      if @statement.update_attributes(params[:statement])
        format.html { redirect_to @statement, :notice => 'Statement was successfully updated.' }
        format.json { head :no_content }
      else
        format.html { render :action => "edit" }
        format.json { render :json => @statement.errors, :status => :unprocessable_entity }
      end
    end
  end

  # DELETE /statements/1
  # DELETE /statements/1.json
  def destroy
    @statement = Statement.find(params[:id])
    @statement.destroy

    respond_to do |format|
      format.html { redirect_to statements_url }
      format.json { head :no_content }
    end
  end
end
