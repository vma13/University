# -*- coding: utf-8 -*-
class DisciplinesController < ApplicationController
  before_filter :check_admin_user, :except=>['index', 'show']
  
  def index
    respond_to do |format|
      format.html {@disciplines = Discipline.page(params[:page])}
      format.json do
        @disciplines = Discipline.where("lower(full_name) LIKE lower(?)","%#{params[:q]}%").all
        render :json=>@disciplines.map(&:attributes)
      end
    end
  end

  def show
    @discipline = @dis = Discipline.includes(:courses).find(params[:id])
  end

  def new
    @discipline = Discipline.new
  end

  def edit
    @discipline = Discipline.find(params[:id])
  end

  def create
    @discipline = Discipline.new(params[:discipline])
    if @discipline.save
      redirect_to @discipline, :notice=>'Дисциплина добавлена.'
    else
      render :action => "new"
    end
  end

  def update
    @discipline = Discipline.find(params[:id])
    if @discipline.update_attributes(params[:discipline])
      redirect_to @discipline, :notice=>'Дисциплина удалена.'
    else
      render :action => "edit"
    end
  end

  def destroy
    @discipline = Discipline.find(params[:id])
    @discipline.destroy
    redirect_to disciplines_url, :notice=>"Дисциплина удалена."
  end
end
